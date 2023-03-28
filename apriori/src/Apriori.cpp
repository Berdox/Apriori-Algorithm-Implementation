#include "../include/Apriori.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::map<std::string, int> Apriori::readDataBase(int& count) {
    std::map<std::string, int> collection;
    std::fstream file;
    file.open(dataBaseName);

    if(!file.is_open()) {
        std::cout << "not open" << std::endl;
    }

    std::string line;

    // read the database
    while (getline (file, line)) {

        while(line.size() != 0) {
            //checks to if a ',' exist in the string line
            int pos = line.find(",");

            if(pos == -1) {
                //',' doesn't exists so it must be at the end of the string
                // adds to the map if the key exist already or inserts a new one
                if(collection.find(line) != collection.end()) {
                    collection[line] += 1;
                } else {
                    collection.insert(std::make_pair(line, 1));
                }

                line.clear();

            } else {
                //',' exists
                // adds to the map if the key exist already or inserts a new one
                std::string sub = line.substr(0, pos);

                if(collection.find(sub) != collection.end()) {
                    collection[sub] += 1;
                } else {
                    collection.insert(std::make_pair(sub, 1));
                }
                // shrinks the string down by the substring "i1, i3" -> "i3"
                line.erase(0, sub.length()+1);
            }
        }
        //counts how many lines it reads
        count++;
    }

    for(auto i : collection) {
        std::cout << "key " << i.first << " Value " << i.second << std::endl;
    }

    file.close();

    return collection;
}

std::map<std::string, int> Apriori::scanDataBase(std::map<std::string, int> collection) {
    std::fstream file;
    file.open(dataBaseName);

    if(!file.is_open()) {
        std::cout << "not open" << std::endl;
    }

    std::string line;

    // read the database
    while (getline (file, line)) {

        std::map<std::string, int> pairs;

        while(line.size() != 0) {
            //checks to if a ',' exist in the string line
            int pos = line.find(",");

            if(pos == -1) {
                //',' doesn't exists so it must be at the end of the string
                // adds to the map if the key exist already or inserts a new one
                if(pairs.find(line) != pairs.end()) {
                    pairs[line] += 1;
                } else {
                    pairs.insert(std::make_pair(line, 1));
                }

                line.clear();

            } else {
                //',' exists
                // adds to the map if the key exist already or inserts a new one
                std::string sub = line.substr(0, pos);

                if(pairs.find(sub) != pairs.end()) {
                    pairs[sub] += 1;
                } else {
                    pairs.insert(std::make_pair(sub, 1));
                }
                // shrinks the string down by the substring "i1, i3" -> "i3"
                line.erase(0, sub.length()+1);
            }
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

std::map<std::string, int> Apriori::aprioriRun(std::string db, float minSup) {
    int transactionNum = 0;
    dataBaseName = db;
    std::map<std::string, int> collection = readDataBase(transactionNum);


    minSupCount = minSup * float(transactionNum); 
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