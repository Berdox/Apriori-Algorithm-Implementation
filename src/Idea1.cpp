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
        // std::cout<<"transaction: "<<idx<<" ("<<idx%transactions.size()<<")"<<std::endl;

        if(candidateSet.empty()) break;
        auto it = begin(candidateSet);
        while(it!=end(candidateSet)) {
            const itemset &itms = it->first;
            const int &endIdx = it->second;
            // std::cout << "looking for {";
            // for(item x : itms)
            //     std::cout<<x.name<<" ";
            // std::cout<<"} with end: "<<endIdx<<std::endl;
            

            // This candidate has completed 1 full DB scan
            if(idx >= endIdx) {
                // std::cout << "done counting {";
                // for(item x : it->first)
                //     std::cout<<x.name<<" ";
                // std::cout<<"} at idx: "<<idx<<std::endl;
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

                // std::cout<<"found itemset {";
                // for(item x : itms)
                //     std::cout<<x.name<<" ";
                // std::cout<<"}\n";
                
                freqTable[itms]++;
                if(freqTable[itms] >= minSupCount && !frequent.count(itms)) {
                    // std::cout<<"frequent!"<<std::endl;
                    frequent.insert(itms);
                    
                    int K = itms.size();
                    for(const itemset &other_frequent : frequent) {
                        if((int)other_frequent.size() != K) continue;

                        // For two candidate sets, see if K-1 items match
                        int k = 0;
                        auto itemsetA = itms.begin();
                        auto itemsetB = other_frequent.begin();
                 
                        // std::cout<<"comparing with {";
                        // for(item x : other_frequent)
                        //     std::cout<<x.name<<" ";
                        // std::cout<<"}"<<std::endl;
                        
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

                            // std::cout<<"creating new itemset {";
                            // for(item x : newItemset)
                            //     std::cout<<x.name<<" ";
                            // std::cout<<"} at idx: "<<idx+transactions.size()<<std::endl;
                            
                            candidateSet.insert({
                                    newItemset,
                                    idx+(int)transactions.size()
                                });
                        }
                    }
                }
            }
            ++it;
        }

        idx++;
    }

    return idx;
}

double Idea1::aprioriRun(std::set<itemset> &frequent) {
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

    std::map<itemset,int> freqTable;
    int scanCount = 0;
    while(!candidateSet.empty()) {
        dbScans += (double)(scanDataBase(scanCount, freqTable, candidateSet,
                                    frequent) % (int)transactions.size())
                / transactions.size();
        std::cout<<"Scans completed: "<<dbScans<<std::endl;
        scanCount++;
    }

    return dbScans;
}
