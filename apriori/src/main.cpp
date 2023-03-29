#include <iostream>
#include <string>
#include "../include/Apriori.h"

/*
 * Usage:
 * ./apriori <filename>
 */

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cerr << "no filename provided" << std::endl;
        return -1;
    }

    std::string filename = argv[1];

    Apriori a(filename, 0.22);
    a.aprioriRun();
    return 0;
}
