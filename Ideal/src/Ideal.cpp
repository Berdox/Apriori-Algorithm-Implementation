#include "../include/Ideal.h"
#include <iostream>
#include <fstream>

std::map<std::string, int> Ideal::readDataBase(std::string dataBaseName, int& count) {
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



std::map<std::string, int> Ideal::idealRun(std::string db, float minSup) {
    int transactionNum = 0;
    std::map<std::string, int> collection = readDataBase(db, transactionNum);
}