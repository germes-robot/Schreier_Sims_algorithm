#ifndef SCHREIER_SIMS_ALGORITHM_TEST_H
#define SCHREIER_SIMS_ALGORITHM_TEST_H

#include <cstddef>

#define DO_CHECK(EXPR) check(EXPR, __func__, __FILE__, __LINE__)

class Test
{
public:
    static int failedNum; // failed test count
    static int totalNum;  // total test count

public:

    /*
     * if expr failed, function check prints information about error; this information contains test name
     * name of file with test and number of line, where function check is used.
     */
    static void check(bool expr, const char *func, const char *filename, size_t lineNum);

    /*
     * Prints final information about failed and total count of tests
     */
    static void showFinalResult();


    /*
     * This function runs all tests
     */
    virtual void runAllTests() = 0;
};

#endif //SCHREIER_SIMS_ALGORITHM_TEST_H
