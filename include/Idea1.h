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
    int aprioriRun(std::vector<itemset> &frequent_itemsets);

  private:
  
    /* .
     * Supply both a frequency table to populate, and the candidate set to look
     * for.
     * Returns the size of the frequency table.
     */
    int scanDataBase(std::map<itemset,int> &freqTable,
            std::set<itemset> &candidateSet);
};

#endif
