#ifndef STATE_H
#define STATE_H

#include "STATE_NAME.h"
#include "Transition.h"

#include <map>

class State {
private:
    std::map<STATE_NAME, Transition> transitions;

public:
    State(){};
    
    State(
        std::map<STATE_NAME, 
        Transition> state
    );
    
    std::map<STATE_NAME, Transition> getMapTransitions();
    Transition getTransition(STATE_NAME name);
};

#endif