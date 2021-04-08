// #pragma once
#include "Scanner.h"
#include "States.h"
#include <stack>
#include <iostream>


class Parser {
    Scanner S;
    State curState; // можно сразу брать в Scanner
    State curGraph;
    std::string curStr;
    std::string testStr;
    std::stack<State> stackTrace;

private:
    State getNewState() {
        
        curStr = S.getLex();
        curState = S.getState();
        State newState = findState();
        
        if(newState == ERROR) 
            return newState;

        return newState;
    }

    State findState() {
        for(auto& i: mapGraph[curGraph][curState]) {            
            if(i.second.count(curStr)) return i.first;
        }

        if(curStr == "" && S.isEof()) return FILE_END;
        if(curStr == "") return EMPTY_STR;
        return ERROR;
    }

public:
    Parser(const char* filename) : S(filename), curState(MAIN), curGraph(MAIN){
        stackTrace.push(MAIN);
    };

    void printTest() {
        std::cout << "TEST_STR: " << testStr << '\n';
    }

    
    bool checkBrakesSystem() {
        std::stack<bool> check;

        for(auto& c : testStr) {
            if(c == '[') 
                check.push(1);
            if(c == ']') {
                if(check.empty()) return false;
                check.pop();
            }
        }

        return true;
    }

    bool run() {
        int i = 0;
        while(true) {
            State newState = getNewState(); // тут мы получили новое состояние надо его проверить
            switch (newState) {
                case FILE_END:  // нужно проверить реально ли это конец графа
                    while(endStates[curGraph].count(curState)) {
                        curState = curGraph;
                        stackTrace.pop();
                        curGraph = stackTrace.empty() ? MAIN : stackTrace.top();
                    }

                    if(stackTrace.empty()){
                        std::cout << "Congratulations\n";
                        return 1;
                        // return FILE_END;
                    } else {
                        std::cout << "ERROR FILE_END\n";
                        return 0;
                        // return ERROR;
                    }
                    
                    break;
                    
                case EMPTY_STR:
                    std::cout << "HERE\n";
                    if(endStates[curGraph].count(curState)) { // пустая строка и конечное состояние какого то графа
                        curState = curGraph;
                        if(!stackTrace.empty()) stackTrace.pop();
                        curGraph = stackTrace.empty() ? ERROR : stackTrace.top();
                    } 
                    else {
                        std::cout << "ERROR EMPTY_STR\n";
                        return 0;
                        // return ERROR;
                    }
                    break;

                case ERROR:
                    std::cout << "STATE ERROR\n";
                    return 0;
                    // return ERROR;
                    
                default:
                    testStr += marks[curState][newState]; 
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
    Parser P("/Users/nicknamme/Documents/lexangen/ex/input.txt");
    P.run();
    P.printTest();
    std::cout << "CHECK_BRAKE_SYSTEM: " << P.checkBrakesSystem() << '\n';

    return 0;
}