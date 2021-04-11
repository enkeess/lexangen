#include "../include/Transition.h"

Transition::Transition(
    const Mark mark, 
    const std::set<std::string> labels
) :
    mark(mark),
    labels(labels){};

Mark Transition::getMark(){
    return mark;
};

std::set<std::string> Transition::getSetLabels(){
    return labels;
};
