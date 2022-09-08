#include "SchreierStabChain.h"

#include <utility>
#include <set>
#include <iostream>


SchreierStabChain::SchreierStabChain(size_t n, vector<Permutation> permutations, bool DEBUG) : count(n)
        , strongGenerators(std::move(permutations))
        , DEBUG(DEBUG)
{
    base.reserve(n);
    base.push_back(0);
    build();
}

static vector<Permutation> getVectorFromList(const std::initializer_list<std::string> &gens)
{
    vector<Permutation> perms;
    perms.reserve(gens.size());
    for (auto &v : gens)
    {
        perms.emplace_back(v);
    }
    return perms;
}

static void processPermutation(Permutation &permutation,
                               vector<Permutation> &newG, size_t count, Permutation used2[55][55])
{
    for (size_t i = 1; i <= count; i++)
    {
        if (permutation(i) == i)
        {
            continue;
        }
        else
        {
            int j = permutation(i);
            if (used2[i][j].size() != 0)
            {
                permutation = permutation.inverse() * used2[i][j];
            }
            else
            {
                used2[i][j] = permutation;
                newG.push_back(permutation);
            }
        }
    }
}

void SchreierStabChain::build()
{
    vector<Permutation> currentG = strongGenerators;
    for (int k = 1; currentG.size() > 0; k++)
    {
        base.push_back(k);
        trees.emplace_back(SchreierTree(currentG, base[k]));

        if (DEBUG)
        {
            std::cout << "BaseElement: " << k << " | образующих: " << currentG.size() << " | Размер дерева Шрайера: "
                      << trees.back().size() << std::endl;
        }

        const auto &currentTree = trees.back();
        const auto &orbit = currentTree.getOrbit();

        vector<Permutation> newG;
        Permutation used2[55][55];

        for (auto y : orbit)
        {
            for (const auto &perm : currentG)
            {
                //Здесь нужно учитывать, что "ребра" в образующих шраера в другую сторону, то есть получающиеся
                //перестановки надо развернуть.

                auto permutation = currentTree.getWay(perm.getNext(y)) * perm * currentTree.getWay(y).inverse();

                //auto str = permutation.toString();
                processPermutation(permutation, newG, count, used2);
            }
        }
        currentG.swap(newG);
    }

    groupSize = 1;
    for (const auto &tree : trees)
        groupSize *= tree.size();

    baseSize = base.size();
}

SchreierStabChain::SchreierStabChain(size_t n, std::initializer_list<std::string> list)
        : SchreierStabChain(n, getVectorFromList(list), 0)
{
}

BigInteger SchreierStabChain::getGroupSize() const
{
    return groupSize;
}


bool SchreierStabChain::hasPermutation(Permutation permutation)
{
    for (size_t i = 1; i < baseSize; i++)
    {
        auto next = permutation.getNext(i);
        if (!trees[i - 1].contains(next))
        {
            return false;
        }
        permutation = trees[i - 1].getWay(next) * permutation;
    }
    return permutation.toString() == "id";
}


size_t SchreierStabChain::getBaseSize() const
{
    return baseSize;
}

bool SchreierStabChain::hasPermutation(const std::string &permutation)
{
    if (permutation == "id")
    {
        return true;
    }
    return hasPermutation(Permutation(permutation));
}

void SchreierStabChain::printAllGroup() const
{
    printing(0, Permutation());
}

void SchreierStabChain::printing(size_t lvl, Permutation permutation) const
{
    if (lvl == baseSize - 1)
    {
        std::cout << permutation.toString() << "\n";
        return;
    }
    for (const auto &treePermutation : trees[lvl].getTreePermutations())
    {
        printing(lvl + 1, treePermutation * permutation);
    }
}
