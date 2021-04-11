#pragma once

#include "Mark.h"
#include <set>


class Transition {

private:
    Mark mark;
    std::set<std::string> labels;

public:
    Transition(){};
    Transition(
        const Mark mark, 
        const std::set<std::string> labels
    );

    Mark getMark();
    std::set<std::string> getSetLabels();
};