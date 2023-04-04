#ifndef APRIORI_H_INCLUDED
#define APRIORI_H_INCLUDED

#include <string>
#include <map>
#include <set>
#include <vector>
#include <ostream>

struct item {
    std::string name;
};

typedef std::set<item> itemset;

class Apriori {
  public:
    Apriori(std::string dbName, double minSup);
    ~Apriori() {}
    
    /* Implementation of the Apriori algorithm.
     * Supply a vector of itemsets to populate with results of algorithm.
     * Returns the number of DB scans performed.
     */
    int aprioriRun(std::vector<itemset> &frequent_itemsets);

  private:
    double minSup;
    int minSupCount;

    std::vector<itemset> transactions;

    /* Reads initial itemsets from file.
     * Supply name of file to read from.
     * Returns number of itemsets read and populates the 'transactions' vector
     * for future reference.
     */
    int readDataBase(std::string dbName);
  
    /* Scans through the initial database to count the occurences of each
     * itemset in 'candidateSet'.
     * Supply both a frequency table to populate, and the candidate set to look
     * for.
     * Returns the size of the frequency table.
     */
    int scanDataBase(std::map<itemset,int> &freqTable,
            std::set<itemset> &candidateSet);
    
};

#endif
