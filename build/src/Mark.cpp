#include "../include/Mark.h"

Mark::Mark() :
    bracket(NONE),
    id(""){};

Mark::Mark(MARK_BRACKET bracket) :
    bracket(bracket),
    id(""){};

Mark::Mark(
    MARK_BRACKET bracket, 
    std::string id
) :
    bracket(bracket),
    id(id) {};

MARK_BRACKET Mark::getBracket() {
    return bracket;
};

std::string Mark::getId() {
    return id;
};