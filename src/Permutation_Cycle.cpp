#include <stdexcept>
#include <iostream>
#include <utility>
#include "Permutation.h"

Permutation::Cycle::Cycle(std::string s)
{
    if (s.size() <= 2 || s[0] != '(' || s.back() != ')')
    {
        throw std::logic_error("Неправильный формат цикла");
    }

    elements.reserve(s.size());
    s.erase(0, 1);
    s.back() = ' ';

    size_t position = 0;
    while (true)
    {
        size_t nextSpace = s.find(' ', position);
        if (nextSpace >= s.size())
        {
            break;
        }

        elements.emplace_back(std::stoi(
                s.substr(position, nextSpace - position)));
        position = nextSpace + 1;
    }
    elements.shrink_to_fit();

    normalize();
    countNext();
}

Permutation::Cycle::Cycle(vector<int> vec) : elements(std::move(vec))
{
    normalize();
    countNext();
}

void Permutation::Cycle::print() const
{
    std::cout << toString() << std::endl;
}

void Permutation::Cycle::normalize()
{
    std::rotate(elements.begin(), std::min_element(elements.begin(), elements.end()), elements.end());
}

int Permutation::Cycle::get(int k) const
{
    return next.at(k);
}

int Permutation::Cycle::getMax() const
{
    return next.rbegin()->first;
}

const vector<int> &Permutation::Cycle::getElements() const
{
    return elements;
}



std::string Permutation::Cycle::toString() const
{
    std::string answer = "(";
    for (size_t i = 0; i < elements.size() - 1; i++)
        answer += std::to_string(elements[i]) + " ";
    answer += std::to_string(elements.back());
    answer += ")";
    return answer;
}

void Permutation::Cycle::countNext()
{
    for (size_t i = 0; i < elements.size() - 1; i++)
        next[elements[i]] = elements[i + 1];
    next[elements.back()] = elements[0];
}

