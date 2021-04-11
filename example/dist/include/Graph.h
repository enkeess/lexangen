#ifndef GRAPH_H
#define GRAPH_H

#include "State.h"

class Graph {
private:
    STATE_NAME start;  // начальное состояние
    std::set<STATE_NAME> ends; // конечные состояния
    std::map<STATE_NAME, State> states;    // состояния

public:
    Graph(){};

    Graph(
        STATE_NAME start, 
        std::set<STATE_NAME> ends, 
        std::map<STATE_NAME, State> states
    );

    STATE_NAME getStart();
    std::set<STATE_NAME> getEnds();
    std::map<STATE_NAME, State> getMapStates();
    State getState(const STATE_NAME name);
};

#endif