#include "../include/Idea1.h"
#include "../include/Timer.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
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
    std::set<itemset> frequent_itemsets;

    Timer t;
    double dbScans = a.aprioriRun(frequent_itemsets);
    auto idea1_time = t.elapsed();

    // Making the output file name
    std::fstream file;
    int posD = filename.find("D");
    int posTxt = filename.find("txt") - 1;
    std::stringstream stream;
    stream << std::fixed << std::setprecision(4) << min_sup;
    std::string support = stream.str();
    support.erase(0,2);
    std::string outputFile = "./results/" + filename.substr(posD, posTxt - posD) + "_idea1_" +
                                                         support + ".freq";
 
    file.open(outputFile, std::ios::app);

    file << "Frequent Itemsets: [size]" << std::endl;
    //std::cout << "Frequent Itemsets: [size]" << std::endl;

    for(const itemset &s:frequent_itemsets) {
        file << "{";
        for(auto i:s)
            file <<i.name<<",";
        file <<"} - ["<<(int)s.size()<<"]\n";

        /*std::cout << "{";
        for(auto i:s)
            std::cout<<i.name<<",";
        std::cout<<"} - ["<<(int)s.size()<<"]\n";*/
    }

    file << (int)frequent_itemsets.size() << " itemsets found in "
              << std::fixed << std::setprecision(1) << dbScans << " scans"
              << std::endl;

    file << std::fixed << std::setprecision(2)
              << "Time taken " << idea1_time << "s" << std::endl;

    file.close();

    std::cout << "The frequent itemsets are stored in " << outputFile 
              << ", under ms = " << min_sup << std::fixed << std::setprecision(2) 
              << ". \nThe time spent is " << idea1_time 
              << "s, to get the frequent itemsets. \nThe number of times scanning"  
              << " the database is " << std::fixed << std::setprecision(1) << dbScans
              << " to get the frequent itemsets. \n";

    /*std::cout << (int)frequent_itemsets.size() << " itemsets found in "
              << std::fixed << std::setprecision(1) << dbScans << " scans"
              << std::endl;

    std::cout << std::fixed << std::setprecision(2)
              << "Time taken " << idea1_time << "s" << std::endl;*/
    return 0;
}
