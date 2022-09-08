#include <iostream>
#include <vector>

#include "Permutation.h"
#include "SchreierTree.h"
#include "SchreierStabChain.h"

using namespace std;

static Permutation firstTypeShuffle(size_t sz = 54)
{
    //На три стопки и положить третью между первой и второй
    //123 456 789 -> 123 789 456
    vector<int> next(sz + 1, -1);
    for (size_t i = 1; i <= sz; i++)
    {
        next[i] = i;
    }
    for (size_t i = sz / 3 + 1; i <= 2 * sz / 3; i++)
    {
        swap(next[i], next[i + sz / 3]);
    }
    return Permutation(next);
}

static Permutation secondTypeShuffle(size_t sz = 54)
{
    //На две стопки и одну на другую

    std::vector<int> next(sz + 1, -1);
    for (size_t i = 1; i <= sz; i++)
    {
        if (i % 2 == 0)
        {
            next[i] = i / 2 + sz / 2;
        }
        else
        {
            next[i] = (i + 1) / 2;
        }
    }
    return Permutation(next);
}

static Permutation thirdTypeShuffle(size_t sz = 54)
{
    std::vector<int> next(sz + 1, -1);
    next[1] = sz - 1;
    next[2] = sz;
    for (size_t i = 3; i <= sz; i++)
        next[i] = i - 2;

    return Permutation(next);
}

int main()
{
    auto timer = clock();
    //freopen("output.txt", "w", stdout);
    SchreierStabChain chain(54, {firstTypeShuffle(), secondTypeShuffle(), thirdTypeShuffle()}, true);
    std::cout << chain.getGroupSize() << endl;
    cout << (clock() - timer) / CLOCKS_PER_SEC;
    return 0;
}