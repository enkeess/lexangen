#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <fstream>
#include <sys/stat.h>

#include "../src/rapidjson/document.h"
#include "../src/rapidjson/writer.h"
#include "../src/rapidjson/stringbuffer.h"
#include "../src/rapidjson/istreamwrapper.h"

#include <string>
#include <vector>
#include <set>

using namespace rapidjson;

class FileReader {
    std::ifstream inputStreamFile;
    std::ofstream stateName_h;
    std::ofstream dependencies_h;
    std::ofstream dependencies_cpp;
    std::set<std::string> stateNames;
    std::vector<std::string> graphNames;
    std::vector<std::string> upperGraphNames;
    int tabCounter;

private:

    void outOpen();
    void outClose();

    std::string getTabs();
    std::string getState(std::string str);
    std::string upperCase(std::string str);
    
    void readMark(const Value& mark);
    void readTransition(const Value& transition);
    void readState(const Value& state);
    void readGraph(const Value& graph);


public:
    FileReader(const char* inputStreamFile);
    void parseJson();
};

#endif