#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>
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

    std::string transactions = "";
    
    // Shuffles the vector to make random items to fill the transaction
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(itemList.begin(), itemList.end(), std::default_random_engine(seed));

    // Adds the items to the transaction
    //transactions += "{";
    for(int i = 0; i < num; i++) {
        transactions += itemList[i];
        if(i != num-1) {
            transactions += ", ";
        }
    }
    //transactions += "}";
    return transactions;
}

int main () {

    // Generate the i0 - i99 and store in a vector
    std::vector<std::string> list = GenItems();

    for(auto x : list) {
        std::cout << x << std::endl;
    }


    std::fstream output;

    // Generating the seed for the rand
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::srand(seed);

    /*//Generate Small test database
    output.open("testDatabase.txt", std::ios::app);
    for(int i = 0; i < 10; i++) {
        output << GenTransaction(std::rand() % 2 + 5, list) << "\n";
    }*/

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

    char c;

    std::cin >> c;

    return 0;
}