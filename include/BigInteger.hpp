#ifndef SCHREIER_SIMS_ALGORITHM_BIGINTEGER_HPP
#define SCHREIER_SIMS_ALGORITHM_BIGINTEGER_HPP

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

class BigInteger
{
private:
    // основание системы счисления (1 000 000 000)
    static const int BASE = 1e9;

    // внутреннее хранилище числа
    std::vector<int> mDigits;

    // знак числа
    bool mIsNegative = false;

    void mRemoveLeadingZeros();

    void mShiftRight();

public:
    // класс-исключение, бросаемое при делении на ноль
    class DivideByZero : public std::exception
    {
    };

    BigInteger();

    BigInteger(std::string);

    BigInteger(signed char);

    BigInteger(unsigned char);

    BigInteger(signed short);

    BigInteger(unsigned short);

    BigInteger(signed int);

    BigInteger(unsigned int);

    BigInteger(signed long);

    BigInteger(unsigned long);

    BigInteger(signed long long);

    BigInteger(unsigned long long);

    friend std::ostream &operator<<(std::ostream &, const BigInteger &);

    operator std::string() const;

    const BigInteger operator+() const;

    const BigInteger operator-() const;

    const BigInteger operator++();

    const BigInteger operator++(int);

    const BigInteger operator--();

    const BigInteger operator--(int);

    friend bool operator==(const BigInteger &, const BigInteger &);

    friend bool operator<(const BigInteger &, const BigInteger &);

    friend bool operator!=(const BigInteger &, const BigInteger &);

    friend bool operator<=(const BigInteger &, const BigInteger &);

    friend bool operator>(const BigInteger &, const BigInteger &);

    friend bool operator>=(const BigInteger &, const BigInteger &);

    friend const BigInteger operator+(BigInteger, const BigInteger &);

    BigInteger &operator+=(const BigInteger &);

    friend const BigInteger operator-(BigInteger, const BigInteger &);

    BigInteger &operator-=(const BigInteger &);

    friend const BigInteger operator*(const BigInteger &, const BigInteger &);

    BigInteger &operator*=(const BigInteger &);

    friend const BigInteger operator/(const BigInteger &, const BigInteger &);

    BigInteger &operator/=(const BigInteger &);

    friend const BigInteger operator%(const BigInteger &, const BigInteger &);

    BigInteger &operator%=(const BigInteger &);

    bool isEven() const;

    bool isOdd() const;

    const BigInteger pow(BigInteger) const;
};

#endif //SCHREIER_SIMS_ALGORITHM_BIGINTEGER_HPP
