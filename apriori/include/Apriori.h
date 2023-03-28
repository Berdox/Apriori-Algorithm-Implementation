
#ifndef APRIRIO_H_INCLUDED
#define APRIRIO_H_INCLUDED

#include <string>
#include <map>
class Apriori {
    public:

    std::map<std::string, int> readDataBase(std::string, int&);
    std::map<std::string, int> prune(std::map<std::string, int>, float);
    std::map<std::string, int> joinItemSets(std::map<std::string, int>);
    std::map<std::string, int> aprioriRun(std::string, float minSup);

    private:

    float minSupCount;
};

#endif