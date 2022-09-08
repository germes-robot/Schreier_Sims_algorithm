#include <iostream>
#include "Permutation.h"

using std::max;
using std::string;

Permutation::Permutation(size_t length) : length(length)
        , next(std::vector<int>(length + 1, -1))
{
    fillNextVectorToId();
}

size_t Permutation::operator()(size_t k) const
{
    if (k > length)
    {
        return k;
    }
    return next[k];
}

Permutation operator*(const Permutation &first, const Permutation &second)
{
    Permutation perm(max(first.size(), second.size()));
    for (int i = 1; i <= perm.size(); i++)
    {
        perm.set(i, first(second(i)));
    }
    return perm;
}

int Permutation::size() const
{
    return length;
}

void Permutation::set(int where, int what)
{
    next[where] = what;
}

int Permutation::getNext(int k) const
{
    return operator()(k);
}

Permutation::Permutation(const string &s) : length(-1)
{
    if (s[0] != '(' || s.back() != ')')
    {
        throw std::logic_error("Неправильный формат ввода");
    }

    vector<Cycle> cycles;
    size_t position = 0;
    while (true)
    {
        size_t closePosition = s.find(')', position);
        if (closePosition >= s.size())
        {
            break;
        }
        cycles.emplace_back(s.substr(position, closePosition - position + 1));
        position = closePosition + 1;
    }
    Permutation permutation;
    while (!cycles.empty())
    {
        permutation = Permutation(cycles.back()) * permutation;
        cycles.pop_back();
    }

    swap(permutation);
}

Permutation::Permutation(const Cycle &cycle)
{
    length = cycle.getMax();
    next.resize(length + 1);
    fillNextVectorToId();

    auto elementsArray = cycle.getElements();
    for (size_t i = 0; i < elementsArray.size() - 1; i++)
    {
        next[elementsArray[i]] = elementsArray[i + 1];
    }
    next[elementsArray.back()] = elementsArray[0];
}

void Permutation::swap(Permutation &other)
{
    std::swap(length, other.length);
    next.swap(other.next);
}

void Permutation::print() const
{
    std::cout << toString();
}

void Permutation::fillNextVectorToId()
{
    for (size_t i = 1; i <= length; i++)
    {
        next[i] = i;
    }
}

Permutation &Permutation::pow(long long int n)
{
    if (n == 0)
    {
        Permutation(size()).swap(*this);
        return *this;
    }
    else if (n < 0)
    {
        pow(-n);
        inverse();
    }
    else
    {
        Permutation another(*this);
        another.pow(n / 2);
        another = another * another;
        if (n % 2)
        {
            another = another * (*this);
        }
        another.swap(*this);
    }
    return *this;
}

Permutation &Permutation::inverse()
{
    Permutation permutation(size());
    for (size_t i = 1; i <= length; i++)
    {
        permutation.set(getNext(i), i);
    }
    swap(permutation);
    return *this;
}

vector<Permutation::Cycle> Permutation::getCycles() const
{
    vector<bool> used(length + 1);
    vector<Cycle> cycles;
    for (size_t i = 1; i <= length; i++)
    {
        if (used[i])
        {
            continue;
        }
        vector<int> elems;
        size_t current = i;
        while (true)
        {
            used[current] = true;
            elems.push_back(current);
            current = next[current];
            if (current == i)
            {
                break;
            }
        }
        cycles.emplace_back(elems);
    }

    std::sort(cycles.begin(), cycles.end(), [](const Permutation::Cycle &a, const Permutation::Cycle &b) {
        return a.getElements()[0] < b.getElements()[0];
    });
    auto ptr = std::remove_if(cycles.begin(), cycles.end(), [](const Permutation::Cycle &a) {
        return a.getElements().size() <= 1;
    });
    cycles.resize(ptr - cycles.begin());
    return cycles;
}

std::string Permutation::toString() const
{
    auto cycles = getCycles();

    if (cycles.empty())
    {
        return "id";
    }

    std::string answer;
    for (const auto &v : cycles)
        answer += v.toString();
    return answer;
}

Permutation::Permutation(Permutation &&other) noexcept
{
    swap(other);
}

Permutation::Permutation(const vector<int> &next) : length(next.size() - 1)
        , next(next)
{
}

Permutation Permutation::getInversed() const
{
    auto ans = *this;
    return ans.inverse();
}

Permutation::Permutation(const char *str) : Permutation(string(str))
{
}





