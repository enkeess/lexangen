#ifndef PARSER_H
#define PARSER_H

#include "Scanner.h"
#include <stack>
#include <list>

class Parser {
    Scanner S;
    STATE_NAME curState; 
    STATE_NAME curGraph;
    std::string curStr;
    std::list<Mark> listOfMarks;
    std::stack<STATE_NAME> stackTrace;

private:
    STATE_NAME getNewState();
    STATE_NAME findState();
    bool checkBrakesSystem();

public:
    Parser(const char* filename);
    
    bool run(); 
};

#endif