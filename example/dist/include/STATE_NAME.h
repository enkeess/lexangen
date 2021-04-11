#ifndef STATE_NAME_H
#define STATE_NAME_H

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

#endif