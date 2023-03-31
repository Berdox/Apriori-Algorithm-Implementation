#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>

// Generates the i0 - i99 items
std::vector<std::string> GenItems () {
    std::vector<std::string> itemList;
    for(int i = 0; i < 100; i++) {
        std::string item = "i" + std::to_string(i);
        itemList.push_back(item);
    }
    return itemList;
}

//Generates the transactions filled with i0 - i99 with a range of 5 - 15 items
std::string GenTransaction(int num, std::vector<std::string> itemList) {

    std::map<int, int> indexs;
    std::string transactions = "";

    //makes an random seletions of indexs
    for(int i = 0; i < num; i++) {
        int ran = std::rand() % 100 + 0;
        if(indexs.find(ran) != indexs.end()) {
            i--;
        } else {
            indexs.insert(std::make_pair(ran, ran));
        }
    }

    for(auto i = indexs.begin(); i != indexs.end(); i++) {
        transactions += itemList[i->first];
        transactions += ", ";
    }
    
    transactions.erase(transactions.size()-2, 2);
    
    return transactions;
}

int main () {

    // Generate the i0 - i99 and store in a vector
    std::vector<std::string> list = GenItems();

    std::fstream output;

    // Generating the seed for the rand
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::srand(seed);

    //Generate 1000
    output.open("D1K.txt", std::ios::app);
    for(int i = 0; i < 1000; i++) {
        output << GenTransaction(std::rand() % 11 + 5, list) << "\n";
    }
    output.close();

    //Generate 10000
    output.open("D10K.txt", std::ios::app);
    for(int i = 0; i < 10000; i++) {
        output << GenTransaction(std::rand() % 11 + 5, list) << "\n";
    }
    output.close();

    //Generate 50000
    output.open("D50K.txt", std::ios::app);
    for(int i = 0; i < 50000; i++) {
        output << GenTransaction(std::rand() % 11 + 5, list) << "\n";
    }
    output.close();

    //Generate 100000
    output.open("D100K.txt", std::ios::app);
    for(int i = 0; i < 100000; i++) {
        output << GenTransaction(std::rand() % 11 + 5, list) << "\n";
    }
    output.close();

    return 0;
}