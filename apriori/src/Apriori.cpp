#include "../include/Apriori.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ostream>
#include <cmath>

Apriori::Apriori(std::string dbName, double minSup) : minSup(minSup) {
    // Perform initial scan of file
    int ret = readDataBase(dbName);
    if(ret == -1) {
        std::cerr << "error initializing apriori" << std::endl;
        return;
    }

    // Threshold for number of occurances to call frequent
    minSupCount = (int)std::ceil(minSup * float(ret)); 
}

int Apriori::readDataBase(std::string dbName) {
    int itemsetCount = 0;

    std::ifstream file;
    file.open(dbName);
    if(!file.is_open()) {
        std::cerr << "unable to open file" << std::endl;
        return -1;
    }

    // Read text file one line at a time. Assumes items are delimited by a
    // comma and a space.
    std::string line;
    while (getline (file, line)) {
        line += ",";
        
        itemset newItemset;
        std::istringstream iss(line);
        std::string item;
        while(iss>>item) {
            item = item.substr(0, item.length()-1);
            newItemset.insert(item);
        }

        transactions.push_back(newItemset);
    }

    file.close();

    return transactions.size();
}

std::vector<itemset> Apriori::aprioriRun() {
    // Assuming no duplicate items can exist in any given transaction, gather
    // the frequencies to compare to minSup
    std::map<itemset,int> candidate;
    for(auto &transaction : transactions) {
        for(auto &item : transaction) {
            itemset newItemset = {item};
            candidate[newItemset]++;
        }
    }

    // Scan candidates for frequent itemsets
    std::vector<itemset> frequent;
    for(auto &[candidateSet, freq] : candidate) {
        if(freq >= minSupCount)
            frequent.push_back(candidateSet);
    }

    return frequent;
}
