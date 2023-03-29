#include <iostream>
#include <string>
#include "../include/Apriori.h"

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cerr << "no filename provided" << std::endl;
        return -1;
    }

    std::string filename = argv[1];

    Apriori a;
    a.aprioriRun(filename, 0.22);
    return 0;
}
