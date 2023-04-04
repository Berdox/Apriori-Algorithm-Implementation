#include "../include/Idea1.h"
#include "../include/Timer.h"
#include <iostream>
#include <iomanip>
#include <string>

/*
 * Usage:
 * ./idea1 <filename> <min_sup>
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
    
    Idea1 a(filename, min_sup);
    std::vector<itemset> frequent_itemsets;

    Timer t;
    int dbScans = a.aprioriRun(frequent_itemsets);
    auto idea1_time = t.elapsed();

    std::cout << "Frequent Itemsets: [size]" << std::endl;
    for(itemset &s:frequent_itemsets) {
        std::cout << "{";
        for(auto i:s)
            std::cout<<i.name<<",";
        std::cout<<"} - ["<<(int)s.size()<<"]\n";
    }

    std::cout << (int)frequent_itemsets.size() << " itemsets found in "
        << dbScans << " scans"<<std::endl;

    std::cout << std::fixed << std::setprecision(2)
              << "Time taken " << idea1_time << "s" << std::endl;
    return 0;
}
