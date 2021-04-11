#include "../include/Scanner.h"
#include "../include/Dependencies.h"

void Scanner::readIntoBuf() {
    while(!inputStreamFile.eof()) {
        inputStreamFile.read(buf, BUFSIZE);
        bufCount = fileSize / BUFSIZE > 0 ? BUFSIZE : fileSize % BUFSIZE;
        fileSize-= BUFSIZE;
    }

    bufPointer = 0;
};

int Scanner::getWordMaxSize(const std::set<std::string>& validStrs) {
    int maxSize = -1;
    int curLength = -1;
    int i = 0;
    for(auto& str:  validStrs) {
        curLength = str.length();
        maxSize = curLength > maxSize ? curLength : maxSize; 
    }

    return maxSize;
}

const std::set<std::string> Scanner::getSetOfStr() {
    std::set<std::string> validStrs;
    for(auto& i : graphs[curGraph].getState(curState).getMapTransitions()) {
        for(auto& label : i.second.getSetLabels()) {
            validStrs.insert(label);
        }
    }

    return validStrs;
};

std::string Scanner::getStrFromBuf(int maxsize) {
    char* start = buf+bufPointer;
    int length = bufPointer + maxsize;
    std::string str = "";
    int bufDev = bufCount - bufPointer;

    while(length > bufDev) { 
        if(bufCount != BUFSIZE) return str += std::string(start, start + bufDev);
        else {
            str += std::string(start, start + bufDev);
            length -= bufDev;
            readIntoBuf();
            bufDev = bufCount - bufPointer;
            start = buf+bufPointer;
        }
    }

    str += std::string(start, start + length);
    return str;
}

std::string Scanner::findStr(const std::set<std::string>& validStrs) {

    int maxSize = getWordMaxSize(validStrs);
    std::string strRange = getStrFromBuf(maxSize);

    for(auto& word: validStrs) {
        if(strRange.find(word) == 0) {
            bufPointer += word.length();
            return word;
        }
    }

    bufPointer-= strRange.length();
    return "";
}


Scanner::Scanner(const char* filename) {
    inputStreamFile.open(filename);
    curState = curGraph =  MAIN;
    bufCount = bufPointer = 0;

    inputStreamFile.seekg(0, inputStreamFile.end);
    fileSize = inputStreamFile.tellg();
    inputStreamFile.seekg(0, inputStreamFile.beg);

    readIntoBuf();
}

bool Scanner::isEof() {
    return inputStreamFile.eof() && bufPointer == bufCount;
}

STATE_NAME Scanner::getState() {
    return curState;
}

void Scanner::setState(STATE_NAME curState) {
    this->curState = curState;
}

STATE_NAME Scanner::getGraph() {
    return curGraph;
}

void Scanner::setGraph(STATE_NAME curGraph) {
    this->curGraph = curGraph;
}

std::string Scanner::getLex() {        
    for(auto& it: graphs) {
        if(it.first == curState) {
            curState = it.second.getStart();
            break;
        }
    }
    
    return findStr(getSetOfStr());    
}