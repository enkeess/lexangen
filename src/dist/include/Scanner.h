#ifndef SCANNER_H
#define SCANNER_H

#include "Dependencies.h"
#include "Graph.h"

#include <fstream>

#define BUFSIZE 255

class Scanner {
    STATE_NAME curGraph;
    STATE_NAME curState;
    std::string lex;
    std::ifstream inputStreamFile;
    int fileSize;
    char buf[BUFSIZE];
    int bufCount; // указатель на вершину буффера
    int bufPointer;

private:
    void readIntoBuf();
    int getWordMaxSize(const std::set<std::string>& validStrs);
    const std::set<std::string> getSetOfStr();
    std::string getStrFromBuf(int maxsize);
    std::string findStr(const std::set<std::string>& validStrs);

public:
    Scanner(const char* filename);
    
    bool isEof();

    STATE_NAME getState();
    STATE_NAME getGraph();

    void setState(STATE_NAME curState);
    void setGraph(STATE_NAME curGraph);

    std::string getLex();
};

#endif