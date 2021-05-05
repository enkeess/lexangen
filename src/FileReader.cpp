#include "../include/FileReader.h"


FileReader::FileReader(const char* inputStreamFile) :
    inputStreamFile(inputStreamFile),
    stateName_h("build/include/STATE_NAME.h"),
    stateName_cpp("build/src/STATE_NAME.cpp"),
    dependencies_h("build/include/Dependencies.h"),
    dependencies_cpp("build/src/Dependencies.cpp"),
    tabCounter(0)
{
    assert(inputStreamFile);
}

FileReader::~FileReader() {
    stateName_h.close();
    stateName_cpp.close();
    dependencies_h.close();
    dependencies_cpp.close();
}


void FileReader::outOpen() {
    stateName_h << "#ifndef STATE_NAME_H\n#define STATE_NAME_H\n\n#include <map>\n#include<string>\n\nenum STATE_NAME {\n";
    stateName_cpp << "#include \"../include/STATE_NAME.h\"\n\nstd::map<STATE_NAME, std::string> mapStateName = {\n";
    dependencies_h << "#ifndef DEPENDENCIES_H\n#define DEPENDENCIES_H\n\n#include \"Graph.h\"\n\n";
    dependencies_cpp << "#include \"../include/Dependencies.h\"\n\n";
}

void FileReader::outClose() {
    for(auto& it: stateNames) {
        stateName_h << '\t' << it << ",\n";
    }

    for(auto& it : stateNames) {
        stateName_cpp << "\t{" << it << ", \"" << it << (it != *(--stateNames.end()) ? "\"},\n" : "\"}\n};");   
    }

    stateName_h << "\tERROR,\n\tEMPTY_STR,\n\tFILE_END\n};\n";
    stateName_h << "\nextern std::map<STATE_NAME, std::string> mapStateName;\n";
    stateName_h << "\n#endif";
    dependencies_h << "\nextern std::map<STATE_NAME, Graph> graphs;\n\n#endif";
}

std::string FileReader::getTabs(){
    return std::string(tabCounter, '\t');
}

std::string FileReader::upperCase(std::string str) {
    for (auto & c: str) c = toupper(c);
    return str;
}

std::string FileReader::getState(std::string str) {
    if(str.find("_") == 0) { // это какой-то подграф
        str = upperCase(str.substr(1));
    } else {
        str = upperGraphNames.back() + '_' + upperCase(str);
    }

    if(!stateNames.count(str)) stateNames.insert(str);

    return str;
}

void FileReader::readMark(const Value& mark) {
    if(mark.IsNull()){
        dependencies_cpp << getTabs() + "Mark(),\n";
        return;
    }

    assert(mark.HasMember("dir"));
    std::string dir = mark["dir"].GetString();

    assert(dir == "OPEN" || dir == "CLOSE");

    assert(mark.HasMember("id"));
    if(mark["id"].IsNull()) {
        dependencies_cpp << getTabs() + "Mark(" + dir+ "),\n";
    } else {
        dependencies_cpp << getTabs() + "Mark(\n";
        tabCounter++;
        dependencies_cpp << getTabs() + dir + ",\n";
        dependencies_cpp << getTabs() + "\"" + mark["id"].GetString() + "\"\n"; 
        tabCounter--;
        dependencies_cpp << getTabs() + "),\n";
    }
}

void FileReader::readTransition(const Value& transition) {
    assert(transition.HasMember("to"));
    std::string to = getState(transition["to"].GetString());
    dependencies_cpp << getTabs() + to + ",\n";
    dependencies_cpp << getTabs() + "Transition(\n";
    tabCounter++;
    assert(transition.HasMember("mark"));
    readMark(transition["mark"]);

    assert(transition.HasMember("labels"));
    const Value& labels = transition["labels"];

    dependencies_cpp << getTabs() + "{\n";
    tabCounter++;
    // тут надо собирать set из переходов и чекать чтобы не было пересечений first
    for(int i = 0; i < labels.Size(); i++) {
        // assert(labels[i].GetString() != ""); // проверка на пустую строку 
        
        dependencies_cpp << getTabs() + "\"" + labels[i].GetString() + "\""+ (i != labels.Size()-1 ? ",\n" : "\n");
    }
    tabCounter--;
    dependencies_cpp << getTabs() + "}\n";

    tabCounter--;
    dependencies_cpp << getTabs() + ")\n";
}

void FileReader::readState(const Value& state) {
    assert(state.HasMember("name"));
    std::string name = getState(state["name"].GetString());
    dependencies_cpp << getTabs() + name + ",\n" + getTabs() + "State(\n";
    tabCounter++;
    dependencies_cpp << getTabs() + "{\n";
    tabCounter++;

    assert(state.HasMember("transitions"));

    const Value& transitions = state["transitions"];
    assert(transitions.IsArray());

    for(int i = 0; i < transitions.Size(); i++) {
        dependencies_cpp << getTabs() + "{\n";
        tabCounter++;
        readTransition(transitions[i]);
        tabCounter--;
        dependencies_cpp << getTabs() + (i != transitions.Size() -1 ? "},\n\n" : "}\n");
    }

    tabCounter--;
    dependencies_cpp << getTabs() + "}\n";
    tabCounter--;
    dependencies_cpp << getTabs() + ")\n";

}

void FileReader::readGraph(const Value& graph) {
    assert(graph.HasMember("name"));
    std::string graphName = graph["name"].GetString();
    if(graphName.find("_") == 0) {
        graphNames.push_back(graphName);
        upperGraphNames.push_back(upperCase(graphName.substr(1)));
        stateNames.insert(upperGraphNames.back());
    } else {
        std::cout<< "ERROR readGraph: " << graphNames.back() << '\n';
        return;
    }

    dependencies_h << "extern Graph " << graphName << ";\n";
    dependencies_cpp << "Graph " << graphName << "(\n";

    tabCounter++;

    assert(graph.HasMember("start"));
    std::string start = graph["start"].GetString();
    
    dependencies_cpp << getTabs() << getState(start) + ",\n";


    assert(graph.HasMember("end"));
    const Value& end = graph["end"];

    assert(end.IsArray());
    dependencies_cpp << getTabs() << "{\n";
    tabCounter++;
    for(int i = 0; i < end.Size(); i++) {
        dependencies_cpp << getTabs() + getState(end[i].GetString());
        dependencies_cpp << (i != end.Size()-1 ? ",\n" : "\n");
    }
    tabCounter--;
    dependencies_cpp << getTabs() << "},\n\n";

    assert(graph.HasMember("states"));
    const Value& states = graph["states"];
    assert(states.IsArray());
    
    dependencies_cpp << getTabs() + "{\n";
    tabCounter++;

    for(int i = 0; i < states.Size(); i++) {
        dependencies_cpp << getTabs() + "{\n";
        tabCounter++;

        readState(states[i]);

        tabCounter--;
        dependencies_cpp << getTabs() + (i != states.Size() - 1 ? "},\n\n" : "}\n");
    }

    tabCounter--;
    dependencies_cpp << getTabs() + "}\n";
    
    tabCounter--;
    dependencies_cpp << getTabs() + ");\n\n";

    return ;
}

void FileReader::parseJson() {
    IStreamWrapper isw(inputStreamFile);
    Document doc;
    doc.ParseStream(isw);

    outOpen();
    
    assert(doc.HasMember("graph"));
    const Value& graph = doc["graph"];

    assert(graph.IsArray());

    for(int i = 0; i < graph.Size(); i++) {
        readGraph(graph[i]);
    }

    dependencies_cpp << "std::map<STATE_NAME, Graph> graphs =\n";
    tabCounter++;

    dependencies_cpp << getTabs() + "{\n";
    tabCounter++;

    for(auto& it: graphNames) {
        dependencies_cpp << getTabs() + "{\n";
        tabCounter++;
        dependencies_cpp << getTabs() + getState(it) + ",\n";
        dependencies_cpp << getTabs() + it + "\n";
        tabCounter--;
        dependencies_cpp << getTabs() + (it != *(--graphNames.end()) ? "},\n\n" : "}\n");
    }

    tabCounter--;
    dependencies_cpp << getTabs() + "};\n\n";

    outClose();

    std::cout << "DONE\n";
}
