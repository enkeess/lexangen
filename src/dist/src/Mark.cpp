#include "../include/Mark.h"

Mark::Mark(MARK_BRACKET bracket = NONE, std::string id = "") :
        bracket(bracket),
        id(id) {};

MARK_BRACKET Mark::getBracket() {
    return bracket;
};

std::string Mark::getId() {
    return id;
};