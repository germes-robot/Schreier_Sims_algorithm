cmake_minimum_required(VERSION 3.15)
project(Schreier_Sims_algorithm)

set(CMAKE_CXX_STANDARD 14)

set(SUPERS "-Werror -Wall -Wextra -pedantic")

SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} ${SUPERS}")

include_directories(Schreier_Sims_algorithm "include")

SET(PERM_CPP src/Permutation.cpp src/Permutation_Cycle.cpp include/Permutation.h)
SET(TEST_FILES test/SchreierSimsTest.cpp test/Test.cpp)
SET(BIG_INT src/BigInteger.cpp include/BigInteger.hpp)
SET(SCHREIER_FILES src/SchreierTree.cpp include/SchreierTree.h src/SchreierStabChain.cpp include/SchreierStabChain.h)

add_executable(TestAlgorithm test/test.cpp ${PERM_CPP} ${TEST_FILES} ${SCHREIER_FILES} ${BIG_INT})
add_executable(FastTest src/main.cpp ${PERM_CPP} ${SCHREIER_FILES} ${BIG_INT})
add_executable(GroupTask my_task/task.cpp ${PERM_CPP} ${SCHREIER_FILES} ${BIG_INT})
add_executable(Demonstration my_task/demonstration.cpp ${PERM_CPP} ${SCHREIER_FILES} ${BIG_INT})