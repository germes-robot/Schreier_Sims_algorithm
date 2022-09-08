#ifndef SCHREIER_SIMS_ALGORITHM_SCHREIERSIMSTEST_H
#define SCHREIER_SIMS_ALGORITHM_SCHREIERSIMSTEST_H

#include "Test.h"
#include "Permutation.h"
#include "SchreierTree.h"

class SchreierSimsTest : Test
{
public:
    void runAllTests() override;

private:
    static void treeTest1();
    static void treeTest2();
    static void treeTest3();

    static void orbitTest1();
    static void orbitTest2();
    static void orbitTest3();

    static void runTreeTests();
    static void runPermutationTests();

    static void runStabChainTests();


    static void stringConstructor1();
    static void stringConstructor2();

    static void multiply1();
    static void multiply2();
    static void multiply3();

    static void pow1();
    static void pow2();
    static void pow3();
    static void pow4();
    static void pow5();

    static void powNegative1();
    static void powNegative2();
    static void powNegative3();

    static void orbitContains1();

    static void orbitContains2();

    static void orbitContains3();

    static void groupSize1();
    static void groupSize2();
    static void groupSize3();
    static void groupSize4();
};


#endif //SCHREIER_SIMS_ALGORITHM_SCHREIERSIMSTEST_H
