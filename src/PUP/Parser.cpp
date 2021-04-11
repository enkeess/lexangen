// #pragma once
#include "Scanner.h"
#include "States.h"
#include <stack>
#include <iostream>


class Parser {
    Scanner S;
    STATE_NAME curState; // можно сразу брать в Scanner
    STATE_NAME curGraph;
    std::string curStr;
    std::list<Mark> listOfMarks;
    std::stack<STATE_NAME> stackTrace;

private:
    STATE_NAME getNewState() {
        
        curStr = S.getLex();
        curState = S.getState();
        STATE_NAME newState = findState();
        
        if(newState == ERROR) 
            return newState;

        return newState;
    }

    STATE_NAME findState() {
        for(auto& i: graphs[curGraph].getState(curState).getMapTransitions()) {
            if(i.second.getSetLabels().count(curStr)) return i.first;    
        }

        if(curStr == "" && S.isEof()) return FILE_END;
        if(curStr == "") return EMPTY_STR;
        return ERROR;
    }

public:
    Parser(const char* filename) : S(filename), curState(MAIN), curGraph(MAIN){
        stackTrace.push(MAIN);
    };
    
    bool checkBrakesSystem() {
        std::stack<Mark> check;
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

        return true;
    }

    bool run() {
        int i = 0;
        while(true) {
            STATE_NAME newState = getNewState(); // тут мы получили новое состояние надо его проверить
            std::cout << "NEW_STATE: " << newState << "  ---  " << curStr <<'\n';
            switch (newState) {
                case FILE_END:  // нужно проверить реально ли это конец графа
                    while(graphs[curGraph].getEnds().count(curState)) {
                        curState = curGraph;
                        stackTrace.pop();
                        curGraph = stackTrace.empty() ? MAIN : stackTrace.top();
                    }

                    if(stackTrace.empty()){
                        std::cout << "Congratulations\n";
                        return checkBrakesSystem();
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
                    listOfMarks.push_back(graphs[curGraph].getState(curState).getTransition(newState).getMark());
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
};

int main() {

    std::cout << "PUP\n";
    Parser P("/Users/nicknamme/Documents/lexangen/ex/input.txt");
    P.run();

    std::cout << P.checkBrakesSystem() << '\n';

    return 0;
}