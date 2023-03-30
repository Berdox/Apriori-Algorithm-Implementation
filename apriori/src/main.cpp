#include <iostream>
#include <string>
#include "../include/Apriori.h"

/*
 * Usage:
 * ./apriori <filename>
 */

int main(int argc, char* argv[]) {
    // Get filename
    if(argc < 2) {
        std::cerr << "no filename provided" << std::endl;
        return -1;
    }
    std::string filename = argv[1];

    // Get filename
    if(argc < 3) {
        std::cerr << "no min_sup provided" << std::endl;
        return -1;
    }
    double min_sup = std::stod(argv[2]);
    
    Apriori a(filename, min_sup);
    auto transactions = a.aprioriRun();

    std::cout << "TRANSACTIONS:" << std::endl;
    for(itemset &s:transactions) {
        std::cout << "{";
        for(auto i:s)
            std::cout<<i<<",";
        std::cout<<"} - ["<<(int)s.size()<<"]\n";
    }

    return 0;
}
