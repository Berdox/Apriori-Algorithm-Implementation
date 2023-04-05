#include "../include/Idea1.h"
#include "../include/Itemset.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

int Idea1::scanDataBase(int scanNo, std::map<itemset,int> &freqTable,
        std::set<std::pair<itemset, int>> &candidateSet,
        std::set<itemset> &frequent) {
    // Look only for occurences of items within the candidate set
    int idx = scanNo * (int)transactions.size();
    while(idx < (scanNo+1) * (int)transactions.size()) {
        auto &transaction = transactions[idx % (int)transactions.size()];

        if(candidateSet.empty()) break;
        auto it = begin(candidateSet);
        while(it!=end(candidateSet)) {
            const itemset &itms = it->first;
            const int &endIdx = it->second;

            // This candidate has completed 1 full DB scan
            if(idx >= endIdx) {
                it = candidateSet.erase(it);
                continue;
            }

            // If intersection of candidate and transaction is == candidate,
            // then it exists within the transaction
            itemset intersection;
            std::set_intersection(begin(itms), end(itms),
                    begin(transaction), end(transaction),
                    std::inserter(intersection, begin(intersection)));

            if(intersection.size() == itms.size()) {
                freqTable[itms]++;

                // Create new candidates only once for each frequent set
                if(freqTable[itms] >= minSupCount && !frequent.count(itms)) {
                    frequent.insert(itms);
                    
                    int K = itms.size();
                    for(const itemset &other_frequent : frequent) {
                        if((int)other_frequent.size() != K) continue;

                        // For two candidate sets, see if K-1 items match
                        int k = 0;
                        auto itemsetA = itms.begin();
                        auto itemsetB = other_frequent.begin();
                 
                        while(k < K-1) {
                            if((*itemsetA).name == (*itemsetB).name) {
                                k++;
                                ++itemsetA;
                                ++itemsetB;
                            } else break;
                        }
                        if(k == K-1) {
                            itemset newItemset = itms;
                            newItemset.insert(*(other_frequent.rbegin()));
                            if(newItemset.size() == itms.size()) continue;

                            candidateSet.insert({
                                    newItemset,
                                    idx+(int)transactions.size()
                                });
                        } else break;
                    }
                }
            }
            ++it; // Next Candidate
        }

        idx++; // Next Transaction
    }

    return idx;
}

double Idea1::aprioriRun(std::set<itemset> &frequent) {
    std::cout << "Running Apriori algorithm with idea 1..." << std::endl;

    // Assuming no duplicate items can exist in any given transaction, gather
    // the inital frequencies from DB
    double dbScans = 1;
    std::set<std::pair<itemset,int>> candidateSet;
    for(auto &transaction : transactions) {
        for(auto &item : transaction) {
            itemset newItemset = {item};
            candidateSet.insert({newItemset,transactions.size()});
        }
    }

    // Continually perform DB scans until there are no more candidates
    std::map<itemset,int> freqTable;
    int scanCount = 0;
    while(!candidateSet.empty()) {
        dbScans += (double)(scanDataBase(scanCount, freqTable, candidateSet,
                                    frequent) % (int)transactions.size())
                / transactions.size();
        scanCount++;
    }

    return dbScans;
}
