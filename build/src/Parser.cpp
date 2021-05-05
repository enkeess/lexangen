#include "../include/Parser.h"
#include "../include/Dependencies.h"
#include <iostream>

STATE_NAME Parser::getNewState() {
    curStr = S.getLex();
    curState = S.getState();
    STATE_NAME newState = findState();
    
    if(newState == ERROR) 
        return newState;

    return newState;
}

STATE_NAME Parser::findState() {
    for(auto& i: graphs[curGraph].getState(curState).getMapTransitions()) {
        if(i.second.getSetLabels().count(curStr)) return i.first;    
    }

    if(curStr == "" && S.isEof()) return FILE_END;
    if(curStr == "") return EMPTY_STR;
    return ERROR;
}

Parser::Parser(const char* filename) : 
    S(filename), 
    curState(MAIN), 
    curGraph(MAIN)
{
    stackTrace.push(MAIN);
};

bool Parser::checkBrakesSystem() {
    std::stack<Mark> check;
    std::cout << "Brakes system -> ";
    for(auto& it: listOfMarks) {
        std::cout << (it.getBracket() == OPEN ? "(" : ")") << (it.getId() != "" ? "_{" + it.getId() + "} " : " ");
    }
    std::cout << '\n';
    for(auto& it: listOfMarks) {
        if(it.getBracket() == OPEN) {
            check.push(it);
        }
        if(it.getBracket() == CLOSE) {
            if(check.empty() || check.top().getId() != it.getId()) 
                return false;
            check.pop();
        }
    }

    

    return check.empty();
}

bool Parser::run() {
    int i = 0;
    std::cout << "***** TRASE ROUTE *****\n";
    while(true) {
        STATE_NAME newState = getNewState(); // тут мы получили новое состояние надо его проверить
        // std::cout << "NEW_STATE: " << newState << "  ---  " << curStr <<'\n';
        switch (newState) {
            case FILE_END:  // нужно проверить реально ли это конец графа
                while(graphs[curGraph].getEnds().count(curState)) {
                    curState = curGraph;
                    stackTrace.pop();
                    curGraph = stackTrace.empty() ? MAIN : stackTrace.top();
                }

                if(stackTrace.empty()){
                    std::cout << "Congratulations\n";
                    bool check = checkBrakesSystem();
                    std::cout << "Brakes system is " << (check ? "correct" : "uncorrect") << '\n';
                    return check;
                } else {
                    std::cout << "ERROR FILE_END\n";
                    return 0;
                }
                
                break;
                
            case EMPTY_STR:
                if(graphs[curGraph].getEnds().count(curState)) { // пустая строка и конечное состояние какого то графа
                    curState = curGraph;
                    if(!stackTrace.empty()) stackTrace.pop();
                    curGraph = stackTrace.empty() ? ERROR : stackTrace.top();
                } 
                else {
                    std::cout << "ERROR EMPTY_STR\n";
                    return 0;
                }

                break;

            case ERROR:
                std::cout << "STATE ERROR\n";
                return 0;
                
            default:
                std::cout << mapStateName[curState] + " -> " + mapStateName[newState] + ", by: " + curStr + '\n';
                Mark mark = graphs[curGraph].getState(curState).getTransition(newState).getMark();
                if(mark.getBracket()!= NONE) listOfMarks.push_back(mark);
                if(graphs.count(newState)) {
                    stackTrace.push(newState);
                    curGraph = curState = newState;
                    S.setState(newState);
                    S.setGraph(newState);
                }
                else {
                    curState = newState;
                    S.setState(newState);
                }
                break;
        }
    }
}