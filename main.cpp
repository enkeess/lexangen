#include <istream>
#include "include/FileReader.h"

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "INPUT ERROR\n";
        return -1;

    }

    FileReader fr(argv[1]);
    fr.parseJson();
    return 0;
}