#include <istream>
#include <stdio.h>
#include <stdlib.h>
#include "include/FileReader.h"

int main(int argc, char* argv[]) {

    if(argc < 2) {
        std::cout << "INPUT ERROR\n";
        return -1;

    }

    do {
        FileReader fr(argv[1]);
        fr.parseJson();
    } while(false);

    system("echo '\n -- COMPILE -- \n'");
    system("make -C $PWD/build");
    
    system("echo '\nFind result in build'");
    return 0;
}
