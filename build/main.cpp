#include <iostream>
#include "include/Parser.h"

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "INPUT ERROR\n";
        return -1;
    }

    Parser P(argv[1]);
    P.run();
    return 0;
}