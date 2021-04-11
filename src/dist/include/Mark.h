#pragma once

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
    Mark(
        MARK_BRACKET bracket = NONE, 
        std::string id = ""
    );

    MARK_BRACKET getBracket();
    std::string getId();
};