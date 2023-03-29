#include "../include/Apriori.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

int Apriori::readDataBase(std::map<std::string, int> &table) {
    int itemsetCount = 0;

    std::ifstream file;
    file.open(dataBaseName);
    if(!file.is_open()) {
        std::cerr << "unable to open file" << std::endl;
        return -1;
    }

    // Read text file one line at a time. Assumes items are delimited by a
    // comma and a space.
    std::string line;
    while (getline (file, line)) {
        line += ",";
        
        std::istringstream iss(line);
        std::string item;
        while(iss>>item) {
            item = item.substr(0, item.length()-1);
            table[item]++;
        }

        itemsetCount++;
    }

    file.close();

    return itemsetCount;
}

std::map<std::string, int> Apriori::scanDataBase(std::map<std::string, int> collection) {
    std::ifstream file;
    file.open(dataBaseName);
    if(!file.is_open()) {
        std::cout << "not open" << std::endl;
        return collection;
    }

    // read the database
    std::string line;
    while (getline (file, line)) {
        std::map<std::string, int> pairs;

        line += ",";

        std::istringstream iss(line);
        std::string item;
        while(iss>>item) {
            item = item.substr(0, item.length()-1);
            pairs[item]++;
        }

        for(auto it = collection.begin(); it != collection.end(); it++) {
            std::vector<std::string> colFreq;
            std::string freq = it->first;
            std::cout << "freq: " << freq << std::endl;
            for(unsigned int i = 1; i < freq.size(); i++) {
                if(freq[i] == '\n' || freq[i] == 'i') {
                    //std::cout << "sub " << freq.substr(0, i) << '\n';
                    colFreq.push_back(freq.substr(0, i));
                    freq.erase(0, i);
                    i = 1;
                }
                std::cout << "freq2: " << freq << std::endl;
            }
            for(auto p : colFreq) {
                std::cout << "col " << p << '\n';
            }
            std::cout << "break \n";
            /*unsigned int count = 0;
            for(unsigned int i = 0; i < colFreq.size(); i++) {
                if(pairs.find(colFreq[i]) != pairs.end()) {
                    count++;
                }
            }*/

            /*if(count == colFreq.size()) {
                it->second++;
            }*/
        }
    }

    file.close();

    return collection;
}

std::map<std::string, int> Apriori::prune(std::map<std::string, int> collection, float minSup) {
    
    std::vector<std::string> keys;

    for(auto tran : collection) {
        if(float(tran.second) < minSup) {
            keys.push_back(tran.first);
        }
    }

    for(auto key : keys) {
        collection.erase(key);
    }

    return collection;
}

std::map<std::string, int> Apriori::joinItemSets(std::map<std::string, int> collection) {
    std::map<std::string, int> join;
    std::cout << "joinning " << std::endl;
    for(auto it = collection.begin(); it != collection.end(); it++) {
        auto temp = it;
        temp++;
        for(auto itt = temp; itt != collection.end(); itt++) {
            join.insert(std::make_pair((it->first + itt->first), 0));
        }
        
    }

    return join;
}

std::map<std::string, int> Apriori::aprioriRun() {
    // Perform initial scan of file
    std::map<std::string, int> collection;
    int ret = readDataBase(collection);
    if(ret == -1) {
        std::cerr << "error running apriori algorithm" << std::endl;
        return collection;
    }

    minSupCount = (int)(minSup * float(ret)); 
    //while(1) {
        /*for(auto col : collection) {
            std::cout << col.first << " and " << col.second << "\n";
        }*/
        std::map<std::string, int> copy = collection;
    // keep a collection of the last one and then prune and if there is nothing left your done
        collection = prune(collection, minSupCount);

        for(auto col : collection) {
            std::cout << "prune " <<  col.first << " and " << col.second << "\n";
        }

        collection = joinItemSets(collection);

        for(auto col : collection) {
            std::cout << "join " <<  col.first << " and " << col.second << "\n";
        }

        collection = scanDataBase(collection);

        for(auto col : collection) {
            std::cout << "scan " <<  col.first << " and " << col.second << "\n";
        }

    //}

    return collection;
}
