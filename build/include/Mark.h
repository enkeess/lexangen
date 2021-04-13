#ifndef MARK_H
#define MARK_H

#include <string>

enum MARK_BRACKET {
    OPEN,
    CLOSE, 
    NONE
};

class Mark {

private:
    MARK_BRACKET bracket;
    std::string id;

public:
    Mark();
    Mark(MARK_BRACKET bracket);
    Mark(
        MARK_BRACKET bracket, 
        std::string id
    );

    MARK_BRACKET getBracket();
    std::string getId();
};
#endif