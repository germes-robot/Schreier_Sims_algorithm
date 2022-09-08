#ifndef SCHREIER_SIMS_ALGORITHM_SCHREIERSTABCHAIN_H
#define SCHREIER_SIMS_ALGORITHM_SCHREIERSTABCHAIN_H

#include "SchreierTree.h"
#include "BigInteger.hpp"

class SchreierStabChain
{
public:
    SchreierStabChain(size_t n, vector<Permutation> permutations, bool DEBUG);
    SchreierStabChain(size_t n, std::initializer_list<std::string> strs);

    BigInteger getGroupSize() const;
    size_t getBaseSize() const;

    bool hasPermutation(Permutation permutation);

    bool hasPermutation(const std::string &permutation);

    void printAllGroup() const;

private:
    void printing(size_t lvl, Permutation permutation) const;

    void build();

    size_t count;
    vector<Permutation> strongGenerators;
    vector<SchreierTree> trees;

    BigInteger groupSize = 0;
    size_t baseSize = 0;
    vector<int> base;

    const bool DEBUG;
};

#endif //SCHREIER_SIMS_ALGORITHM_SCHREIERSTABCHAIN_H
