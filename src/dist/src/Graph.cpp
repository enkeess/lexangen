#include "../include/Graph.h"

Graph::Graph(
    STATE_NAME start, 
    std::set<STATE_NAME> ends, 
    std::map<STATE_NAME, State> states
) :
    start(start),
    ends(ends),
    states(states) {};

STATE_NAME Graph::getStart(){
    return start;
};

std::set<STATE_NAME> Graph::getEnds(){
    return ends;
};

std::map<STATE_NAME, State> Graph::getMapStates(){
    return states;
};

State Graph::getState(const STATE_NAME name){
    return states[name];
};