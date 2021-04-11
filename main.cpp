#include <istream>
#include "include/FileReader.h"

int main(int argc, char* argv[]) {
    FileReader fr("/Users/nicknamme/Desktop/ex_1.json");
    fr.parseJson();
    return 0;
}