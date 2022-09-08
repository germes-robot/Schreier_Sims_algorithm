#ifndef SCHREIER_SIMS_ALGORITHM_PERMUTATION_H
#define SCHREIER_SIMS_ALGORITHM_PERMUTATION_H

#include <cstddef>
#include <vector>
#include <algorithm>
#include <map>

using std::vector;

class Permutation
{
private:
    class Cycle;
public:
    friend class SchreierSimsTest;

    Permutation(const vector<int> &next);
    Permutation(Permutation &&other) noexcept;
    Permutation(const Permutation &other) = default;
    explicit Permutation(size_t length = 0);
    Permutation(const std::string &s);
    explicit Permutation(const Cycle &cycle);

    Permutation(const char *str);

    Permutation &operator=(const Permutation &other) = default;
    size_t operator()(size_t k) const;

    friend Permutation operator*(const Permutation &, const Permutation &);

    int getNext(int k) const;

    Permutation &pow(long long int n);

    Permutation &inverse();

    Permutation getInversed() const;
    int size() const;
    std::string toString() const;
    void print() const;

    void swap(Permutation &other);

    vector<Cycle> getCycles() const;
private:

    void fillNextVectorToId();

    void set(int where, int what);

    size_t length;
    vector<int> next;
};

class Permutation::Cycle
{
public:
    Cycle() = default;

    explicit Cycle(std::string s);

    explicit Cycle(vector<int> vector);

    int get(int k) const;

    int getMax() const;

    const vector<int> &getElements() const;

    void print() const;

    std::string toString() const;

private:

    void normalize();

    void countNext();

    std::map<int, int> next;
    vector<int> elements;
};

#endif //SCHREIER_SIMS_ALGORITHM_PERMUTATION_H
