#include "../include/Apriori.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ostream>

Apriori::Apriori(std::string dbName, double minSup) : minSup(minSup) {
    // Perform initial scan of file
    int ret = readDataBase(dbName);
    if(ret == -1) {
        std::cerr << "error initializing apriori" << std::endl;
        return;
    }

    // Threshold for number of occurances to call frequent
    minSupCount = (int)(minSup * float(ret)); 
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

// std::map<std::string, int> Apriori::scanDataBase(std::map<std::string, int> collection) {
//     std::ifstream file;
//     file.open(dataBaseName);
//     if(!file.is_open()) {
//         std::cout << "not open" << std::endl;
//         return collection;
//     }
//
//     // read the database
//     std::string line;
//     while (getline (file, line)) {
//         std::map<std::string, int> pairs;
//
//         line += ",";
//
//         std::istringstream iss(line);
//         std::string item;
//         while(iss>>item) {
//             item = item.substr(0, item.length()-1);
//             pairs[item]++;
//         }
//
//         for(auto it = collection.begin(); it != collection.end(); it++) {
//             std::vector<std::string> colFreq;
//             std::string freq = it->first;
//             std::cout << "freq: " << freq << std::endl;
//             for(unsigned int i = 1; i < freq.size(); i++) {
//                 if(freq[i] == '\n' || freq[i] == 'i') {
//                     //std::cout << "sub " << freq.substr(0, i) << '\n';
//                     colFreq.push_back(freq.substr(0, i));
//                     freq.erase(0, i);
//                     i = 1;
//                 }
//                 std::cout << "freq2: " << freq << std::endl;
//             }
//             for(auto p : colFreq) {
//                 std::cout << "col " << p << '\n';
//             }
//             std::cout << "break \n";
//             /*unsigned int count = 0;
//             for(unsigned int i = 0; i < colFreq.size(); i++) {
//                 if(pairs.find(colFreq[i]) != pairs.end()) {
//                     count++;
//                 }
//             }*/
//
//             /*if(count == colFreq.size()) {
//                 it->second++;
//             }*/
//         }
//     }
//
//     file.close();
//
//     return collection;
// }
//
// std::map<std::string, int> Apriori::prune(std::map<std::string, int> collection, float minSup) {
//     
//     std::vector<std::string> keys;
//
//     for(auto tran : collection) {
//         if(float(tran.second) < minSup) {
//             keys.push_back(tran.first);
//         }
//     }
//
//     for(auto key : keys) {
//         collection.erase(key);
//     }
//
//     return collection;
// }
//
// std::map<std::string, int> Apriori::joinItemSets(std::map<std::string, int> collection) {
//     std::map<std::string, int> join;
//     std::cout << "joinning " << std::endl;
//     for(auto it = collection.begin(); it != collection.end(); it++) {
//         auto temp = it;
//         temp++;
//         for(auto itt = temp; itt != collection.end(); itt++) {
//             join.insert(std::make_pair((it->first + itt->first), 0));
//         }
//         
//     }
//
//     return join;
// }
//
std::vector<itemset> Apriori::aprioriRun() {
    return transactions;
}
