//
//  BigInt.cpp
//  BigInt
//
//  Created by Alexey Karpov on 14.03.17.
//  Copyright © 2017 Alexey Karpov. All rights reserved.
//

#include "BigInt.hpp"

void BigInt::set_cap(const int cap)
{
    this->size = cap;
    this->value = new int [this->size];
}
void BigInt::assign(const char *str)
{
    int len = strlen(str);
    int ost;
    if (str[0] == '-')
    {
        this->sign = -1;
        ost = 1;
    } else {
        this->sign = 1;
        ost = 0;
    }
    set_cap((len - ost - 1) / DIGIT_COUNT + 1);
    for (int i  = 0; i < this->size; ++i) {
        value[i] = 0;
        for (int j = len - (i + 1) * DIGIT_COUNT; j < len - (i) * DIGIT_COUNT; j++) {
            if (j >= ost)
            {
                value[i] = (value[i] * 10) + (str[j] - '0');
            }
        }
    }
}
void BigInt::assign(const BigInt &that)
{
    set_cap(that.size);
    this->sign = that.sign;
    for (int i = 0; i < this->size; i++)
    {
        this->value[i] = that.value[i];
    }
}
void BigInt::assign(int value)
{
    long long v = BASE;
    int n = 1;
    if (value < 0)
    {
        this->sign = -1;
        value *= -1;
    } else {
        this->sign = 1;
    }
    while (v < value) {
        v *= BASE;
        n++;
    }
    set_cap(n);
    for (int i  = 0; i < n; i++)
    {
        this->value[i] = value % BASE;
        value /= BASE;
    }
}
void BigInt::assign(unsigned int value)
{
    long long v = BASE;
    int n = 1;
    this->sign = 1;
    while (v < value) {
        v *= BASE;
        n++;
    }
    set_cap(n);
    for (int i  = 0; i < n; i++)
    {
        this->value[i] = value % BASE;
        value /= BASE;
    }
}
void BigInt::assign(long long value)
{
    long long v = BASE;
    int n = 1;
    if (value < 0)
    {
        this->sign = -1;
        value *= -1;
    } else {
        this->sign = 1;
    }
    while (v < value && v <= 9223372036854775807 / BASE) {
        v *= BASE;
        n++;
    }
    if (v >= 9223372036854775807 / BASE)
    {
        n++;
    }
    set_cap(n);
    for (int i  = 0; i < n; i++)
    {
        this->value[i] = value % BASE;
        value /= BASE;
    }
}
void BigInt::assign(unsigned long long value)
{
    unsigned long long v = BASE;
    int n = 1;
    this->sign = 1;
    while (v < value && v <= 18446744073709551615 / BASE) {
        v *= BASE;
        n++;
    }
    if (v >= 18446744073709551615 / BASE)
    {
        n++;
    }
    set_cap(n);
    for (int i  = 0; i < n; i++)
    {
        this->value[i] = value % BASE;
        value /= BASE;
    }
}
BigInt::BigInt() {
    this->size = 0;
}

BigInt::BigInt(const int &value)
{
    assign(value);
}
BigInt::BigInt(const unsigned int &value)
{
    assign(value);
}
BigInt::BigInt(const long long &value)
{
    assign(value);
}
BigInt::BigInt(const unsigned long long &value)
{
    assign(value);
}

BigInt::BigInt(char *str)
{
    assign(str);
}

BigInt::BigInt(const BigInt &that)
{
    assign(that);
}
BigInt::~BigInt()
{
    delete [] this->value;
}


BigInt BigInt::abs_sum(const BigInt &that) const
{
    if (this->size < that.size)
    {
        return that.abs_sum(*this);
    } else {
        BigInt res;
        res.size = this->size + 1;
        res.set_cap(res.size);
        int ost = 0;
        for (int i = 0; i < that.size; i++)
        {
            res.value[i] = (this->value[i] + that.value[i] + ost) % BASE;
            ost = (this->value[i] + that.value[i] + ost) / BASE;
        }
        for (int i = that.size; i < this->size; i++)
        {
            res.value[i] = (this->value[i] + ost) % BASE;
            ost = (this->value[i] + ost) / BASE;
        }
        if (ost > 0)
        {
            res.value[this->size] = ost;
        } else {
            res.size--;
        }
        res.sign = 1;
        return res;
    }
}
BigInt BigInt::abs_minus(const BigInt &that) const
{
    if (that > *this)
    {
        BigInt res = that.abs_minus(*this);
        res.sign = -1;
        return res;
    } else {
        BigInt res;
        res.size = this->size;
        res.set_cap(res.size);
        int ost = 0;
        for (int i = 0; i < that.size; i++)
        {
            if (that.value[i] > this->value[i] - ost)
            {
                ost = 1;
                res.value[i] = this->value[i] - ost + BASE - that.value[i];
            } else {
                ost = 0;
                res.value[i] = this->value[i] - ost - that.value[i];
            }
        }
        for (int i = that.size; i < this->size; i++)
        {
            if (this->value[i] - ost < 0)
            {
                ost = 1;
                res.value[i] = this->value[i] - ost + BASE - that.value[i];
            } else {
                ost = 0;
                res.value[i] = this->value[i] - ost - that.value[i];
            }
        }
        while (res.value[res.size - 1] == 0 && res.size > 1) {
            res.size--;
        }
        res.sign = 1;
        return res;
    }
}

ostream& operator<<(ostream& res, const BigInt &a)
{
    if (a.sign == -1 && a.value[a.size - 1] != 0)
        res << '-';
    for (int i = a.size - 1; i >= 0; i--)
    {
        int d = a.BASE / 10;
        int &v = a.value[i];
        while (i < a.size - 1 && d > v + 1) {
            res << '0';
            d /= 10;
        }
        cout << a.value[i] << " ";
    }
    cout << endl;
    return res;
}
istream& operator>>(istream& in, BigInt &a)
{
    char str[1000];
    in >> str;
    delete [] a.value;
    a.assign(str);
    return in;
}



BigInt &BigInt::operator=(const BigInt &that)
{
    delete [] this->value;
    assign(that);
    return *this;
}
BigInt &BigInt::operator=(const char *str)
{
    delete [] this->value;
    assign(str);
    return *this;
}
BigInt &BigInt::operator=(int value)
{
    delete [] this->value;
    assign(value);
    return *this;
}
bool BigInt::operator>(const BigInt &that) const
{
    if (this->size < that.size) {
        return false;
    } else {
        if (this->size > that.size)
        {
            return true;
        } else {
            int i = this->size - 1;
            while (that.value[i] == this->value[i])
            {
                i--;
            }
            if (this->value[i] > that.value[i])
            {
                return true;
            } else {
                return false;
            }
        }
    }
}
bool BigInt::operator==(const BigInt &that) const
{
    if (this->size != that.size)
    {
        return false;
    } else {
        bool flag = true;
        for (int i = 0; i < this->size; i++)
        {
            if (this->value[i] != that.value[i])
                flag = false;
        }
        return flag;
    }
}
bool BigInt::operator<(const BigInt &that) const
{
    if (*this > that || *this == that)
    {
        return false;
    } else {
        return true;
    }
}
BigInt BigInt::operator+(const BigInt &that) const
{
    if (this->sign == that.sign)
    {
        if (this->sign == 1)
        {
            return abs_sum(that);
        } else {
            BigInt res = abs_sum(that);
            res.sign = -1;
            return res;
        }
    } else {
        if (this->sign == -1)
        {
            return that.abs_minus(*this);
        } else {
            return abs_minus(that);
        }
    }
}
BigInt BigInt::operator-(const BigInt &that) const
{
    if (this->sign == that.sign)
    {
        if (this->sign == 1)
        {
            return abs_minus(that);
        } else {
            BigInt res = abs_minus(that);
            res.sign = res.sign * (-1);
            return res;
        }
    } else {
        if (this->sign == -1)
        {
            BigInt res = abs_sum(that);
            res.sign = -1;
            return res;
        } else {
            return abs_sum(that);
        }
    }
}
BigInt &BigInt::operator+=(const BigInt &that)
{
    *this = *this + that;
    return *this;
}
BigInt &BigInt::operator-=(const BigInt &that)
{
    *this = *this - that;
    return *this;
}
BigInt BigInt::operator+(const int &value) const
{
    BigInt that(value);
    return *this + that;
}
BigInt BigInt::operator+(const unsigned int &value) const
{
    BigInt that(value);
    return *this + that;
}
BigInt BigInt::operator+(const long long &value) const
{
    BigInt that(value);
    return *this + that;
}
BigInt BigInt::operator+(const unsigned long long &value) const
{
    BigInt that(value);
    return *this + that;
}
BigInt BigInt::operator-(const int &value) const
{
    BigInt that(value);
    return *this - that;
}
BigInt BigInt::operator-(const unsigned int &value) const
{
    BigInt that(value);
    return *this - that;
}
BigInt BigInt::operator-(const long long &value) const
{
    BigInt that(value);
    return *this - that;
}
BigInt BigInt::operator-(const unsigned long long &value) const
{
    BigInt that(value);
    return *this - that;
}
BigInt &BigInt::operator+=(const int &value)
{
    BigInt that(value);
    return *this += that;
}
BigInt &BigInt::operator+=(const unsigned int &value)
{
    BigInt that(value);
    return *this += that;
}
BigInt &BigInt::operator+=(const long long &value)
{
    BigInt that(value);
    return *this += that;
}
BigInt &BigInt::operator+=(const unsigned long long &value)
{
    BigInt that(value);
    return *this += that;
}
BigInt &BigInt::operator-=(const int &value)
{
    BigInt that(value);
    return *this -= that;
}
BigInt &BigInt::operator-=(const unsigned int &value)
{
    BigInt that(value);
    return *this -= that;
}
BigInt &BigInt::operator-=(const long long &value)
{
    BigInt that(value);
    return *this -= that;
}
BigInt &BigInt::operator-=(const unsigned long long &value)
{
    BigInt that(value);
    return *this -= that;
}



