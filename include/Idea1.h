#ifndef IDEA1_H_INCLUDED
#define IDEA1_H_INCLUDED

#include "./Apriori.h"

class Idea1 : protected Apriori {
  public:
    Idea1(std::string dbName, double minSup) : Apriori(dbName, minSup) {};
    ~Idea1() {}
    
    /* Implementation of the Apriori algorithm with Idea1.
     * Supply a vector of itemsets to populate with results of algorithm.
     * Returns the number of DB scans performed.
     */
    double aprioriRun(std::set<itemset> &frequent_itemsets);

  private:
  
    /* .
     * Supply both a frequency table to populate, and the candidate set to look
     * for.
     * Returns the last index considered in the transaction list.
     */
    int scanDataBase(int scanNo, std::map<itemset,int> &freqTable,
            std::set<std::pair<itemset,int>> &candidateSet,
            std::set<itemset> &frequent);
};

#endif
