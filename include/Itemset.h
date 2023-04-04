#ifndef ITEMSET_H_INCLUDED
#define ITEMSET_H_INCLUDED

#include <set>
#include <string>

struct item {
    std::string name;
};

typedef typename std::set<item> itemset;

inline bool operator<(const item &a, const item &b) {
    // Sort numerically by item name instead of lexicographically.
    // i.e i5 should be less than i25
    return std::stoi(a.name.substr(1)) < std::stoi(b.name.substr(1));
}

inline bool operator<(const itemset &a, const itemset &b) {
    // Ensure itemsets are sorted in lexicographical order
    return std::lexicographical_compare(begin(a), end(a), begin(b), end(b));
}

#endif // ITEMSET_H_INCLUDED
