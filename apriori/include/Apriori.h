
#ifndef APRIORI_H_INCLUDED
#define APRIORI_H_INCLUDED

#include <string>
#include <map>
#include <set>

typedef std::set<std::string> itemset;

class Apriori {
  public:
    Apriori(std::string dbName, float minSup)
        : dataBaseName(dbName), minSup(minSup) {}

    /* Reads initial itemsets from file.
     * Supply table to fill by reference as 'table'
     * Returns number of itemsets read
     */
    int readDataBase(std::map<std::string, int> &table);
    
    std::map<std::string, int> scanDataBase(std::map<std::string, int>);
    std::map<std::string, int> prune(std::map<std::string, int>, float);
    std::map<std::string, int> joinItemSets(std::map<std::string, int>);
    std::map<std::string, int> aprioriRun();

  private:
    std::string dataBaseName;
    float minSup;
    int minSupCount;
};

#endif
