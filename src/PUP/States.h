#pragma once
#include <map>
#include <set>
#include <list>
#include <vector>
#include <string>

enum STATE_NAME { 
// graph _main
    MAIN,
    MAIN_A,
    MAIN_B,
// graph _C
    C,
    C_A,
// служебные состояния
    ERROR,
    EMPTY_STR,
    FILE_END
};

enum MARK_BRACKET {
    OPEN,  // (
    CLOSE, // )
    NONE
};

class Mark {
    MARK_BRACKET bracket;
    std::string id;

public:
    Mark(MARK_BRACKET bracket = NONE, std::string id = "") {
        this->bracket = bracket;
        this->id = id;
    };

    MARK_BRACKET getBracket() {
        return bracket;
    };

    std::string getId() {
        return id;
    };
};

class Transition {
    Mark mark;
    std::set<std::string> labels;

public:
    Transition(){};
    Transition(const Mark mark, const std::set<std::string> labels) :
        mark(mark),
        labels(labels){};

    Mark getMark() {
        return mark;
    };

    std::set<std::string> getSetLabels() {
        return labels;
    };

    Transition(const Transition& transition) :
        mark(transition.mark), 
        labels(transition.labels) {};

    Transition& operator=(const Transition& transition){
        if (this != &transition) {
            mark = transition.mark;
            labels = transition.labels;
        }

        return *this;
    };
};

class State {
    std::map<STATE_NAME, Transition> transitions;

public:
    State(){};
    State(std::map<STATE_NAME, Transition> state) :
        transitions(state){};

    std::map<STATE_NAME, Transition> getMapTransitions(){
        return transitions;
    }

    Transition getTransition(STATE_NAME name) {
        return transitions[name];
    };

};

class Graph {
    STATE_NAME start;  // начальное состояние
    std::set<STATE_NAME> ends; // конечные состояния
    std::map<STATE_NAME, State> states;    // состояния

public:

    Graph(){};

    Graph(
        STATE_NAME start, 
        std::set<STATE_NAME> ends, 
        std::map<STATE_NAME, State> states
    ){
        this->start = start;
        this->ends = ends;
        this->states = states;
    };

    Graph(const Graph& graph) :
        start(graph.start),
        ends(graph.ends),
        states(graph.states) {}

    STATE_NAME getStart(){
        return start;
    }

    std::set<STATE_NAME> getEnds(){
        return ends;
    };

    std::map<STATE_NAME, State> getMapStates(){
        return states;
    }

    State getState(const STATE_NAME name){
        return states[name];
    };

};

Graph _main (
    MAIN_A,
    {
        MAIN_B,
        C
    },
    {
        {   
            MAIN_A,
            State(
                {
                    {
                        MAIN_A,
                        Transition(
                            Mark(OPEN),
                            {
                                "a"
                            }
                        )
                    },

                    {
                        MAIN_B,
                            Transition(
                            Mark(CLOSE),
                            {
                                "b"
                            }
                        )
                    }
                }
            )
        },

        {
            MAIN_B,
            State(
                {
                    {
                        MAIN_B,
                        Transition(
                            Mark(CLOSE),
                            {
                                "b"
                            }
                        )
                    },

                    {
                        C,
                        Transition(
                            Mark(),
                            {
                                "c"
                            }
                        )
                    }
                }
            )
        }
    }
);

Graph _C (
    C_A,
    {
        C_A
    },
    {
        {
            C_A,
            State(
                {
                    {
                        C_A,
                        Transition( 
                            Mark(),
                            {
                                "c"
                            }
                        )   
                    }
                    
                }
            )
        }
    }
);

std::map<STATE_NAME, Graph> graphs = 
                         {
                            {
                                MAIN, 
                                _main
                            },
                            {
                                C, 
                                _C
                            }                                
                         };





