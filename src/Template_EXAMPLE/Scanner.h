#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "States.h"

#define BUFSIZE 255

class Scanner {
    State curGraph;
    State curState;
    std::string lex;
    std::ifstream inputStreamFile;
    int fileSize;
    char buf[BUFSIZE];
    int bufCount; // указатель на вершину буффера
    int bufPointer;

private:
    const setOfStr getSetOfStr() {
        setOfStr validStrs;
        for(auto& i : mapGraph[curGraph][curState]) {
            for(auto& j : i.second) {
                validStrs.insert(j);
            }
        }

        return validStrs;
    };

    void readIntoBuf() {
        while(!inputStreamFile.eof()) {
            inputStreamFile.read(buf, BUFSIZE);
            bufCount = fileSize / BUFSIZE > 0 ? BUFSIZE : fileSize % BUFSIZE;
            fileSize-= BUFSIZE;
        }

        bufPointer = 0;
    };

    int getWordMaxSize(const setOfStr& validStrs) {
        int maxSize = -1;
        int curLength = -1;
        int i = 0;
        for(auto& str:  validStrs) {
            curLength = str.length();
            maxSize = curLength > maxSize ? curLength : maxSize; 
        }

        return maxSize;
    }

    std::string getStrFromBuf(int maxsize) {
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

    std::string findStr(const setOfStr& validStrs) {

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

public:
    Scanner(const char* filename) {
        inputStreamFile.open(filename);
        curState = curGraph =  MAIN;
        bufCount = bufPointer = 0;

        inputStreamFile.seekg(0, inputStreamFile.end);
        fileSize = inputStreamFile.tellg();
        inputStreamFile.seekg(0, inputStreamFile.beg);

        readIntoBuf();
    }
    
    bool isEof() {
        return inputStreamFile.eof() && bufPointer == bufCount;
    }

    State getState() {
        return curState;
    }

    void setState(State curState) {
        this->curState = curState;
    }

    State getGraph() {
        return curGraph;
    }

    void setGraph(State curGraph) {
        this->curGraph = curGraph;
    }

    std::string getLex() {        
        switch (curState) {
            case MAIN:  
                curState = startStates[MAIN];
                break;
            case C:
                curState = startStates[C];
                break;
            default:
                break;
        };
        
        return findStr(getSetOfStr());     
    }
};