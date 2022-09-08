#include "SchreierSimsTest.h"
#include <Permutation.h>
#include <iostream>
#include <SchreierStabChain.h>

void SchreierSimsTest::runAllTests()
{
    std::cout << std::endl;

    runPermutationTests();
    runTreeTests();

    runStabChainTests();

    showFinalResult();
}

void SchreierSimsTest::multiply1()
{
    Permutation first("(1 2 3)");
    Permutation second("(3 2 1)");
    DO_CHECK((first * second).toString() == "id");
}

void SchreierSimsTest::multiply2()
{
    Permutation first("(1 2 3)");
    Permutation second("(3 4 2)");
    DO_CHECK((first * second).toString() == "(1 2)(3 4)");
}

void SchreierSimsTest::multiply3()
{
    Permutation first("(11 10 6 8)");
    Permutation second("(5 8 6 3)");
    DO_CHECK((first * second).toString() == "(3 5 11 10 6)");
}

void SchreierSimsTest::pow1()
{
    Permutation perm("(1 2)");
    DO_CHECK(perm.pow(1e9).toString() == "id");
}

void SchreierSimsTest::pow2()
{
    Permutation perm("(1 2 3)");
    DO_CHECK(perm.pow(1).toString() == "(1 2 3)");
}

void SchreierSimsTest::pow3()
{
    Permutation perm("(1 2 3)");
    DO_CHECK(perm.pow(2).toString() == "(1 3 2)");
}

void SchreierSimsTest::pow4()
{
    Permutation perm("(1 2)");
    DO_CHECK(perm.pow(1e9 + 1).toString() == "(1 2)");
}

void SchreierSimsTest::pow5()
{
    Permutation perm("(1 2 3)");
    DO_CHECK(perm.pow(3).toString() == "id");
}

void SchreierSimsTest::stringConstructor2()
{
    Permutation perm("(1 2 3)(3 2 1)(1 2)(2 1)(4 5 6 7)(7 6 5 4)");
    DO_CHECK(perm.toString() == "id");
}

void SchreierSimsTest::stringConstructor1()
{
    Permutation perm("(1)");
    DO_CHECK(perm.toString() == "id");
}

void SchreierSimsTest::powNegative1()
{
    Permutation perm("(1 2 3)");
    DO_CHECK(perm.pow(-1).toString() == "(1 3 2)");
}

void SchreierSimsTest::powNegative2()
{
    Permutation perm("(2 4 3 5)");
    DO_CHECK(perm.pow(-2).toString() == "(2 3)(4 5)");
}

void SchreierSimsTest::powNegative3()
{
    Permutation perm("(1 10 2)");
    DO_CHECK(perm.pow(-1e9).toString() == "(1 2 10)");
}

void SchreierSimsTest::runPermutationTests()
{
    stringConstructor1();
    stringConstructor2();

    multiply1();
    multiply2();
    multiply3();

    pow1();
    pow2();
    pow3();
    pow4();
    pow5();

    powNegative1();
    powNegative2();
    powNegative3();

}

void SchreierSimsTest::runTreeTests()
{
    treeTest1();
    treeTest2();
    treeTest3();

    orbitTest1();
    orbitTest2();
    orbitTest3();

    orbitContains1();
    orbitContains2();
    orbitContains3();
}

void SchreierSimsTest::treeTest1()
{
    SchreierTree tree({"(2 8 7)", "(1 3 5)", "(7 3)"}, 1);

    const auto &gens = tree.generators;
    const auto &pNum = tree.parentNumber;

    DO_CHECK(gens[pNum.at(5)].toString() == "(1 3 5)"
             && gens[pNum.at(7)].toString() == "(3 7)"
             && gens[pNum.at(2)].toString() == "(2 8 7)"
             && tree.calcWay(2).toString() == "(1 5 3 7 8 2)");
}

void SchreierSimsTest::treeTest2()
{
    SchreierTree tree({"(1 2)", "(1 3)", "(2 4)", "(3 4)"}, 1);

    const auto &gens = tree.generators;
    const auto &pNum = tree.parentNumber;

    DO_CHECK(gens[pNum.at(3)].toString() == "(1 3)"
             && gens[pNum.at(2)].toString() == "(1 2)"
             && gens[pNum.at(4)].toString() == "(2 4)"
             && tree.calcWay(4).toString() == "(1 2 4)");
}

void SchreierSimsTest::treeTest3()
{
    SchreierTree tree({"(1 2)", "(1 3)", "(2 3)"}, 3);

    const auto &gens = tree.generators;
    const auto &pNum = tree.parentNumber;

    DO_CHECK(gens[pNum.at(2)].toString() == "(2 3)"
             && gens[pNum.at(1)].toString() == "(1 3)"
             && tree.calcWay(2).toString() == "(2 3)"
             && tree.calcWay(3).toString() == "id"
             && tree.calcWay(1).toString() == "(1 3)");
}

void SchreierSimsTest::orbitTest1()
{
    SchreierTree tree({"(1 2)", "(4 5 3)", "(3 8 7 2)"}, 1);
    DO_CHECK(tree.getOrbit() == vector<int>({1, 2, 3, 4, 5, 7, 8}));
}

void SchreierSimsTest::orbitTest2()
{
    SchreierTree tree({"(17 21)", "(21 13)", "(4 5 6)"}, 17);
    DO_CHECK(tree.getOrbit() == vector<int>({13, 17, 21}));
}

void SchreierSimsTest::orbitTest3()
{
    SchreierTree tree({"(17 21)", "(21 13)", "(4 5 6)"}, 8);
    DO_CHECK(tree.getOrbit() == vector<int>({8}));
}

void SchreierSimsTest::orbitContains1()
{
    SchreierTree tree({"(17 21)", "(21 13)", "(4 5 6)"}, 8);
    DO_CHECK(!tree.contains(17));
}

void SchreierSimsTest::orbitContains2()
{
    SchreierTree tree({"(17 21)", "(21 13)", "(4 5 6)"}, 17);
    DO_CHECK(tree.contains(13) && tree.contains(21));
}

void SchreierSimsTest::orbitContains3()
{
    SchreierTree tree({"(1 2)", "(4 5 3)", "(3 8 7 2)"}, 1);
    DO_CHECK(tree.contains(5) && tree.contains(8));
}

void SchreierSimsTest::runStabChainTests()
{
    groupSize1();
    groupSize2();
    groupSize3();
    groupSize4();
}

void SchreierSimsTest::groupSize1()
{
    SchreierStabChain stabChain(1, {});
    DO_CHECK(stabChain.getGroupSize() == 1);
}

void SchreierSimsTest::groupSize2()
{
    SchreierStabChain stabChain(3, {"(1 2)", "(2 3)"});
    DO_CHECK(stabChain.getGroupSize() == 6);
}

void SchreierSimsTest::groupSize3()
{
    SchreierStabChain stabChain(3, {"(1 2)", "(2 3)"});
    DO_CHECK(stabChain.getGroupSize() == 6);
}

void SchreierSimsTest::groupSize4()
{
    SchreierStabChain stabChain(5, {"(1 2)", "(4 5 1)", "(2 4)"});
    DO_CHECK(stabChain.getGroupSize() == 12);
}





