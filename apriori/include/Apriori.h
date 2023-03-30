
#ifndef APRIORI_H_INCLUDED
#define APRIORI_H_INCLUDED

#include <string>
#include <map>
#include <set>
#include <vector>
#include <ostream>

typedef std::set<std::string> itemset;

class Apriori {
  public:
    Apriori(std::string dbName, double minSup);
    ~Apriori() {}
    
    std::vector<itemset> aprioriRun();

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
    
    // std::map<std::string, int> scanDataBase(std::map<std::string, int>);
    // std::map<std::string, int> prune(std::map<std::string, int>, float);
    // std::map<std::string, int> joinItemSets(std::map<std::string, int>);
};

#endif
