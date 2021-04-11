#include "../include/State.h"

State::State(std::map<STATE_NAME, Transition> state) :
        transitions(state){};

std::map<STATE_NAME, Transition> State::getMapTransitions(){
    return transitions;
}

Transition State::getTransition(STATE_NAME name) {
    return transitions[name];
};