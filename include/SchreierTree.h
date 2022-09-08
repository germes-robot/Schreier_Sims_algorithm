#ifndef SCHREIER_SIMS_ALGORITHM_SCHREIERTREE_H
#define SCHREIER_SIMS_ALGORITHM_SCHREIERTREE_H

#include <vector>
#include <set>

#include "Permutation.h"

class SchreierTree
{
    friend class SchreierSimsTest;
public:
    SchreierTree(vector<Permutation> gens, int head);

    SchreierTree(std::initializer_list<std::string> gens, int head);

    void print() const;

    size_t size() const;
    const vector<int> &getOrbit() const;

    bool contains(int element) const;

    const vector<Permutation> &getTreePermutations() const;

    Permutation getWay(int k) const;

private:
    Permutation calcWay(int k) const;

    void build();

    void fillTreePermutations();

    mutable std::set<int> orbitSet;

    Permutation wayAt[55];
    std::vector<int> orbit;
    std::map<int, int> parentNumber;
    std::vector<Permutation> generators;
    std::vector<Permutation> oppositeGenerators;
    int head;

    std::vector<Permutation> treePermutations;
};


#endif //SCHREIER_SIMS_ALGORITHM_SCHREIERTREE_H
