#include "BigInteger.hpp"


// создает длинное целое число со значением 0
BigInteger::BigInteger()
{
    this->mIsNegative = false;
}

// создает длинное целое число из C++-строки
BigInteger::BigInteger(std::string str)
{
    if (str.length() == 0)
    {
        this->mIsNegative = false;
    }
    else
    {
        if (str[0] == '-')
        {
            str = str.substr(1);
            this->mIsNegative = true;
        }
        else
        {
            this->mIsNegative = false;
        }

        for (long long i = str.length(); i > 0; i -= 9)
        {
            if (i < 9)
            {
                this->mDigits.push_back(atoi(str.substr(0, i).c_str()));
            }
            else
            {
                this->mDigits.push_back(atoi(str.substr(i - 9, 9).c_str()));
            }
        }

        this->mRemoveLeadingZeros();
    }
}

// удаляет ведущие нули
void BigInteger::mRemoveLeadingZeros()
{
    while (this->mDigits.size() > 1 && this->mDigits.back() == 0)
        this->mDigits.pop_back();

    if (this->mDigits.size() == 1 && this->mDigits[0] == 0)
    {
        this->mIsNegative = false;
    }
}

// печатает число в поток вывода
std::ostream &operator<<(std::ostream &os, const BigInteger &bi)
{
    if (bi.mDigits.empty())
    {
        os << 0;
    }
    else
    {
        if (bi.mIsNegative)
        {
            os << '-';
        }
        os << bi.mDigits.back();
        char old_fill = os.fill('0');
        for (long long i = static_cast<long long>(bi.mDigits.size()) - 2; i >= 0; --i)
            os << std::setw(9) << bi.mDigits[i];
        os.fill(old_fill);
    }

    return os;
}

// сравнивает два числа на равенство
bool operator==(const BigInteger &left, const BigInteger &right)
{
    if (left.mIsNegative != right.mIsNegative)
    {
        return false;
    }

    if (left.mDigits.empty())
    {
        return right.mDigits.empty() || (right.mDigits.size() == 1 && right.mDigits[0] == 0);
    }

    if (right.mDigits.empty())
    {
        return left.mDigits.size() == 1 && left.mDigits[0] == 0;
    }

    if (left.mDigits.size() != right.mDigits.size())
    {
        return false;
    }

    for (size_t i = 0; i < left.mDigits.size(); ++i)
        if (left.mDigits[i] != right.mDigits[i])
        {
            return false;
        }

    return true;
}

// возвращает копию переданного числа
const BigInteger BigInteger::operator+() const
{
    return BigInteger(*this);
}

// возвращает переданное число с другим знаком
const BigInteger BigInteger::operator-() const
{
    BigInteger copy(*this);
    copy.mIsNegative = !copy.mIsNegative;
    return copy;
}

// проверяет, является ли левый операнд меньше правого
bool operator<(const BigInteger &left, const BigInteger &right)
{
    if (left == right)
    {
        return false;
    }
    if (left.mIsNegative)
    {
        if (right.mIsNegative)
        {
            return ((-right) < (-left));
        }
        else
        {
            return true;
        }
    }
    else if (right.mIsNegative)
    {
        return false;
    }
    else
    {
        if (left.mDigits.size() != right.mDigits.size())
        {
            return left.mDigits.size() < right.mDigits.size();
        }
        else
        {
            for (long long i = left.mDigits.size() - 1; i >= 0; --i)
            {
                if (left.mDigits[i] != right.mDigits[i])
                {
                    return left.mDigits[i] < right.mDigits[i];
                }
            }
            return false;
        }
    }
}

// сравнивает два числа на неравенство
bool operator!=(const BigInteger &left, const BigInteger &right)
{
    return !(left == right);
}

// проверяет, является ли левый операнд меньше либо равен правого
bool operator<=(const BigInteger &left, const BigInteger &right)
{
    return (left < right || left == right);
}

// проверяет, является ли левый операнд больше правого
bool operator>(const BigInteger &left, const BigInteger &right)
{
    return !(left <= right);
}

// проверяет, является ли левый операнд больше либо равен правого
bool operator>=(const BigInteger &left, const BigInteger &right)
{
    return !(left < right);
}

// складывает два числа
const BigInteger operator+(BigInteger left, const BigInteger &right)
{
    if (left.mIsNegative)
    {
        if (right.mIsNegative)
        {
            return -(-left + (-right));
        }
        else
        {
            return right - (-left);
        }
    }
    else if (right.mIsNegative)
    {
        return left - (-right);
    }
    int carry = 0;
    for (size_t i = 0; i < std::max(left.mDigits.size(), right.mDigits.size()) || carry != 0; ++i)
    {
        if (i == left.mDigits.size())
        {
            left.mDigits.push_back(0);
        }
        left.mDigits[i] += carry + (i < right.mDigits.size() ? right.mDigits[i] : 0);
        carry = left.mDigits[i] >= BigInteger::BASE;
        if (carry != 0)
        {
            left.mDigits[i] -= BigInteger::BASE;
        }
    }

    return left;
}

// прибавляет к текущему числу новое
BigInteger &BigInteger::operator+=(const BigInteger &value)
{
    return *this = (*this + value);
}

// префиксный инкремент
const BigInteger BigInteger::operator++()
{
    return (*this += 1);
}

// преобразует число к строке
BigInteger::operator std::string() const
{
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

// преобразует signed char к big_integer
BigInteger::BigInteger(signed char c)
{
    this->mIsNegative = c < 0;
    this->mDigits.push_back(std::abs(c));
}

// преобразует unsigned char к big_integer
BigInteger::BigInteger(unsigned char c)
{
    this->mIsNegative = false;
    this->mDigits.push_back(c);
}

// преобразует signed short к big_integer
BigInteger::BigInteger(signed short s)
{
    this->mIsNegative = s < 0;
    this->mDigits.push_back(std::abs(s));
}

// преобразует unsigned short к big_integer
BigInteger::BigInteger(unsigned short s)
{
    this->mIsNegative = false;
    this->mDigits.push_back(s);
}

// преобразует signed int к big_integer
BigInteger::BigInteger(signed int i)
{
    this->mIsNegative = i < 0;
    this->mDigits.push_back(std::abs(i) % BigInteger::BASE);
    i /= BigInteger::BASE;
    if (i != 0)
    {
        this->mDigits.push_back(std::abs(i));
    }
}

// преобразует unsigned int к big_integer
BigInteger::BigInteger(unsigned int i)
{
    this->mDigits.push_back(i % BigInteger::BASE);
    i /= BigInteger::BASE;
    if (i != 0)
    {
        this->mDigits.push_back(i);
    }
}

// преобразует signed long к big_integer
BigInteger::BigInteger(signed long l)
{
    this->mIsNegative = l < 0;
    this->mDigits.push_back(std::abs(l) % BigInteger::BASE);
    l /= BigInteger::BASE;
    if (l != 0)
    {
        this->mDigits.push_back(std::abs(l));
    }
}

// преобразует unsigned long к big_integer
BigInteger::BigInteger(unsigned long l)
{
    this->mDigits.push_back(l % BigInteger::BASE);
    l /= BigInteger::BASE;
    if (l != 0)
    {
        this->mDigits.push_back(l);
    }
}

// преобразует signed long long к big_integer
BigInteger::BigInteger(signed long long l)
{
    if (l < 0)
    {
        this->mIsNegative = true;
        l = -l;
    }
    else
    {
        this->mIsNegative = false;
    }
    do
    {
        this->mDigits.push_back(l % BigInteger::BASE);
        l /= BigInteger::BASE;
    } while (l != 0);
}

// преобразует unsigned long long к big_integer
BigInteger::BigInteger(unsigned long long l)
{
    this->mIsNegative = false;
    do
    {
        this->mDigits.push_back(l % BigInteger::BASE);
        l /= BigInteger::BASE;
    } while (l != 0);
}

// постфиксный инкремент
const BigInteger BigInteger::operator++(int)
{
    *this += 1;
    return *this - 1;
}

// префиксный декремент
const BigInteger BigInteger::operator--()
{
    return *this -= 1;
}

// постфиксный декремент
const BigInteger BigInteger::operator--(int)
{
    *this -= 1;
    return *this + 1;
}

// вычитает два числа
const BigInteger operator-(BigInteger left, const BigInteger &right)
{
    if (right.mIsNegative)
    {
        return left + (-right);
    }
    else if (left.mIsNegative)
    {
        return -(-left + right);
    }
    else if (left < right)
    {
        return -(right - left);
    }
    int carry = 0;
    for (size_t i = 0; i < right.mDigits.size() || carry != 0; ++i)
    {
        left.mDigits[i] -= carry + (i < right.mDigits.size() ? right.mDigits[i] : 0);
        carry = left.mDigits[i] < 0;
        if (carry != 0)
        {
            left.mDigits[i] += BigInteger::BASE;
        }
    }

    left.mRemoveLeadingZeros();
    return left;
}

// вычитает из текущего числа новое
BigInteger &BigInteger::operator-=(const BigInteger &value)
{
    return *this = (*this - value);
}

// перемножает два числа
const BigInteger operator*(const BigInteger &left, const BigInteger &right)
{
    BigInteger result;
    result.mDigits.resize(left.mDigits.size() + right.mDigits.size());
    for (size_t i = 0; i < left.mDigits.size(); ++i)
    {
        int carry = 0;
        for (size_t j = 0; j < right.mDigits.size() || carry != 0; ++j)
        {
            long long cur = result.mDigits[i + j] +
                            left.mDigits[i] * 1LL * (j < right.mDigits.size() ? right.mDigits[j] : 0) + carry;
            result.mDigits[i + j] = static_cast<int>(cur % BigInteger::BASE);
            carry = static_cast<int>(cur / BigInteger::BASE);
        }
    }

    result.mIsNegative = left.mIsNegative != right.mIsNegative;
    result.mRemoveLeadingZeros();
    return result;
}

// домножает текущее число на указанное
BigInteger &BigInteger::operator*=(const BigInteger &value)
{
    return *this = (*this * value);
}

// сдвигает все разряды на 1 вправо (домножает на BASE)
void BigInteger::mShiftRight()
{
    if (this->mDigits.size() == 0)
    {
        this->mDigits.push_back(0);
        return;
    }
    this->mDigits.push_back(this->mDigits[this->mDigits.size() - 1]);
    for (size_t i = this->mDigits.size() - 2; i > 0; --i)
        this->mDigits[i] = this->mDigits[i - 1];
    this->mDigits[0] = 0;
}

// делит два числа
const BigInteger operator/(const BigInteger &left, const BigInteger &right)
{
    if (right == 0)
    {
        throw BigInteger::DivideByZero();
    }

    BigInteger b = right;
    b.mIsNegative = false;
    BigInteger result, current;
    result.mDigits.resize(left.mDigits.size());

    for (long long i = static_cast<long long>(left.mDigits.size()) - 1; i >= 0; --i)
    {
        current.mShiftRight();
        current.mDigits[0] = left.mDigits[i];
        current.mRemoveLeadingZeros();
        int x = 0, l = 0, r = BigInteger::BASE;
        while (l <= r)
        {
            int m = (l + r) / 2;
            BigInteger t = b * m;
            if (t <= current)
            {
                x = m;
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }

        result.mDigits[i] = x;
        current = current - b * x;
    }

    result.mIsNegative = left.mIsNegative != right.mIsNegative;
    result.mRemoveLeadingZeros();
    return result;
}

// делит текущее число на указанное
BigInteger &BigInteger::operator/=(const BigInteger &value)
{
    return *this = (*this / value);
}

// возвращает остаток от деления двух чисел
const BigInteger operator%(const BigInteger &left, const BigInteger &right)
{
    BigInteger result = left - (left / right) * right;
    if (result.mIsNegative)
    {
        result += right;
    }
    return result;
}

// присваивает текущему числу остаток от деления на другое число
BigInteger &BigInteger::operator%=(const BigInteger &value)
{
    return *this = (*this % value);
}

// проверяет, является ли текущее число нечетным
bool BigInteger::isEven() const
{
    if (this->mDigits.size() == 0)
    {
        return false;
    }
    return this->mDigits[0] & 1;
}

// проверяет, является ли текущее число четным
bool BigInteger::isOdd() const
{
    return !this->isEven();
}

// возводит текущее число в указанную степень
const BigInteger BigInteger::pow(BigInteger n) const
{
    BigInteger a(*this), result(1);
    while (n != 0)
    {
        if (n.isEven())
        {
            result *= a;
        }
        a *= a;
        n /= 2;
    }

    return result;
}
