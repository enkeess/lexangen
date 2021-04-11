#ifndef DEPENDENCIES_H
#define DEPENDENCIES_H

#include "Graph.h"

const Graph _main (
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

const Graph _C (
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

const std::map<STATE_NAME, Graph> graphs = 
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

#endif