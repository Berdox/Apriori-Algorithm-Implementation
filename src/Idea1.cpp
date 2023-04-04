#include "../include/Idea1.h"
#include "../include/Itemset.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ostream>
#include <cmath>

int Idea1::scanDataBase(std::map<itemset,int> &freqTable,
        std::set<itemset> &candidateSet) {
    // Look only for occurences of items within the candidate set
    for(auto &transaction : transactions) {
        for(itemset i : candidateSet) {
            // If intersection of candidate and transaction is == candidate,
            // then it exists within the transaction
            itemset intersection;
            std::set_intersection(begin(i), end(i),
                    begin(transaction), end(transaction),
                    std::inserter(intersection, begin(intersection)));
            if(intersection.size() == i.size())
                freqTable[i]++;
        }
    }

    return (int)freqTable.size();
}

int Idea1::aprioriRun(std::vector<itemset> &frequent) {
    std::cout << "OOOH USING IDEA1... FANCY" << std::endl;
    // Assuming no duplicate items can exist in any given transaction, gather
    // the inital frequencies from DB
    int dbScans = 1;
    std::set<itemset> candidateSet;
    for(auto &transaction : transactions) {
        for(auto &item : transaction) {
            itemset newItemset = {item};
            candidateSet.insert(newItemset);
        }
    }

    while(!candidateSet.empty()) {
        int K = begin(candidateSet)->size();
        std::cout << "Generating " << K << "-itemsets" << std::endl;

        // Scan DB for candidate itemsets
        std::map<itemset,int> freqTable;
        scanDataBase(freqTable, candidateSet);
        dbScans++;

        // See which itemsets > minSup
        std::vector<itemset> frequent_k;
        for(auto &[candidate, freq] : freqTable) {
            if(freq >= minSupCount)
                frequent_k.push_back(candidate);
        }
        for(itemset &i : frequent_k)
            frequent.push_back(i);

        // Generate new candidate set (Gross...)
        candidateSet.clear();
        if((int)frequent_k.size() == 0) break;
        for(auto it1 = begin(frequent_k); it1 < end(frequent_k)-1; ++it1) {
            auto it2 = it1 + 1;
            while(it2 < end(frequent_k)) {
                // For two candidate sets, see if K-1 items match
                int k = 0;
                auto itemsetA = it1->begin();
                auto itemsetB = it2->begin();
                while(k < K-1) {
                    if((*itemsetA).name == (*itemsetB).name) {
                        k++;
                        ++itemsetA;
                        ++itemsetB;
                    } else break;
                }
                if(k == K-1) {
                    itemset newItemset = *it1;
                    newItemset.insert(*(it2->rbegin()));
                    candidateSet.insert(newItemset);
                    ++it2;
                } else break;
            }
            if(K>1) it1 = it2 - 1;
        }
        std::cout << candidateSet.size() << " candidates" << std::endl;
    }

    return dbScans;
}