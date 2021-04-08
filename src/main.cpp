
// #include "test_func.h"
// #include "json_parser.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

// #include "States.h"

using namespace rapidjson;

class Transition {
    std::string to;
    std::string mark;
    std::set<std::string> labels;

public:
    void setTo(std::string to) {
        this->to = to;
    }

    void setMark(std::string mark) {
        this->mark = mark;
    }

    void setLabels(std::set<std::string> labels) {
        this->labels = labels;
    }
};

class State {
    bool isStartState;
    bool isEndState;
    bool isSubGraph;
    std::string name;
    std::vector<Transition> transitions;

public:
    void setName(const std::string name) {
        this->name = name;
    }

     void setTransitions(std::vector<Transition> transitions) {
        this->transitions = transitions;
    }

    void setStart(bool isStartState) {
        this->isStartState = isStartState;
    }

    void setEnd(bool isEndState) {
        this->isEndState = isEndState;
    }

    void setSubGraph(bool isSubGraph) {
        this->isSubGraph = isSubGraph;
    }
    std::string getName() {
        return name;
    }

};


class Graph {
    std::string name; // имя графа
    std::string start;  // начальное состояние
    std::set<std::string> end; // конечные состояния
    std::vector<State> states;    // состояния
    std::vector<Graph> subGraphs; // подграфы

public:

    Graph() {}
    std::string getName() {
        return name;
    }
    void setName(const std::string name) {
        this->name = name;
    }

    void setStart(const std::string start) {
        this->start = start;
    }

    void setEnd(const std::set<std::string> end) {
        this->end = end;
    }

    void setStates(std::vector<State> states) {
        this->states = states;
    }

    void setSubGraphs(std::vector<Graph> subGraphs) {
        this->subGraphs = subGraphs;
    }

    std::string getStart() {
        return start;
    }

    std::set<std::string> getEnd() {
        return end;
    }
};

class FileReader {
    std::ifstream inputFileStream;
    // Graph main;

private:
    Graph readGraph(const Value& graph);
    State readState(const Value& state, Graph* curGraph);
    Transition readTransition(const Value& transition);

public:
    FileReader(std::string filename) {
        inputFileStream.open(filename);
        assert(inputFileStream);
    }

    Graph parseGraph();
  
};

Graph FileReader::parseGraph() {
    std::cout << "\nIn parseGraph";
    IStreamWrapper isw(inputFileStream);
    Document doc;
    doc.ParseStream(isw);

    assert(doc.HasMember("graph"));
    const Value& graph = doc["graph"];


    assert(graph.IsArray());
    
    
    Graph main = readGraph(graph[0]);

    std::vector<Graph> subGraphs;
    for(int i = 1; i < graph.Size(); i++) {
        subGraphs.push_back(readGraph(graph[i]));
    }

    main.setSubGraphs(subGraphs);

    return main;

};

Graph FileReader::readGraph(const Value& graph) {
    std::cout << "\nIn readGraph";
    Graph curGraph;

    assert(graph.HasMember("name"));
    curGraph.setName(graph["name"].GetString());

    assert(graph.HasMember("start"));
    curGraph.setStart(graph["start"].GetString());

    assert(graph.HasMember("end"));
    const Value& end = graph["end"];

    assert(end.IsArray());
    std::set<std::string> endStates;
    for(int i = 0; i < end.Size(); i++) {
        endStates.insert(end[i].GetString());
    }

    curGraph.setEnd(endStates);

    assert(graph.HasMember("states"));
    const Value& states = graph["states"];
    assert(states.IsArray());

    std::vector<State> graphStates;

    for(int i = 0; i < states.Size(); i++) {
        graphStates.push_back(readState(states[i], &curGraph));
    }

    curGraph.setStates(graphStates);

    return curGraph;
};


State FileReader::readState(const Value& state, Graph* curGraph) {
    std::cout << "\nIn readState";
    State curState;
    assert(state.HasMember("name"));
    curState.setName(state["name"].GetString());
    curState.setStart(curGraph->getStart() == curState.getName());
    curState.setEnd(curGraph->getEnd().count(curState.getName()));

    assert(state.HasMember("transitions"));

    const Value& transitions = state["transitions"];
    assert(transitions.IsArray());

    std::vector<Transition> graphTransitions;

    for(int i = 0; i < transitions.Size(); i++) {
        graphTransitions.push_back(readTransition(transitions[i]));
    }

    curState.setTransitions(graphTransitions);

    return curState;
};

Transition FileReader::readTransition(const Value& transition) {

    std::cout << "\nIn readTransition";

    Transition curTransition;
    assert(transition.HasMember("to"));
    curTransition.setTo(transition["to"].GetString());

    assert(transition.HasMember("mark"));
    if(transition["mark"].IsNull()) {
        curTransition.setTo("");
    }
    else {
        curTransition.setTo(transition["mark"].GetString());
    }
    
    assert(transition.HasMember("labels"));
    const Value& labels = transition["labels"];
    assert(labels.IsArray());
    std::set<std::string> graphLabels;

    for(int i = 0; i < labels.Size(); i++) {
        graphLabels.insert(labels[i].GetString());
    }

    curTransition.setLabels(graphLabels);

    return curTransition;
}




int main() {
    std::string filename = "/Users/nicknamme/Documents/lexangen/ex/ex_1.json";
    Graph test = FileReader(filename).parseGraph();

    std::map< std::string, std::set<std::string> > map;


    return 0;
}