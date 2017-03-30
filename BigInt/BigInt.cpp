//
//  BigInt.cpp
//  BigInt
//
//  Created by Alexey Karpov on 14.03.17.
//  Copyright © 2017 Alexey Karpov. All rights reserved.
//

#include "BigInt.hpp"
#include <cmath>
#include <stdlib.h>


BigIntegerDivisionByZero::BigIntegerDivisionByZero() : logic_error("Division by zero") {};
BigIntegerOverflow::BigIntegerOverflow() : overflow_error("Over flow") {};



void BigInt::set_cap(const int cap)
{
    this->cap = cap;
    this->size = 0;
    this->value = new int [this->cap];
}
void BigInt::delete0(){
    while (this->value[this->size - 1] == 0 && this->size > 1) {
        this->size--;
    }
}




void BigInt::assign(const char *str)
{
    int len = int(strlen(str));
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
    this->size = this->cap;
    for (int i  = 0; i < this->size; i++)
    {
        int value = 0;
        int k = len - (i + 1) * DIGIT_COUNT;
        int start = max(0, k);
        for (int j = start; j < len - (i) * DIGIT_COUNT; j++)
        {
            if (j >= ost)
            {
                value = (value * 10) + (str[j] - '0');
            }
        }
        this->value[i] = value;
    }
}
void BigInt::assign(const BigInt &that)
{
    set_cap(that.size);
    this->size = this->cap;
    this->sign = that.sign;
    memcpy(this->value, that.value, that.size * sizeof(int));
}
void BigInt::assign(const BigInt &that, const int n)
{
    set_cap(n);
    this->size = this->cap;
    this->sign = that.sign;
    int delta = that.size - this->size;
    for (int i = 0; i < this->size; i++)
    {
        this->value[i] = that.value[i + delta];
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
    this->size = this->cap;
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
    this->size = this->cap;
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
    this->size = this->cap;
    for (int i  = 0; i < n; i++)
    {
        this->value[i] = value % BASE;
        value /= BASE;
    }
    delete0();
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
    this->size = this->cap;
    for (int i  = 0; i < n; i++)
    {
        this->value[i] = value % BASE;
        value /= BASE;
    }
    delete0();
}



BigInt::BigInt() {
    this->size = this->cap = 0;
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
BigInt::BigInt(const BigInt &that, const int n)
{
    assign(that, n);
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
        res.set_cap(this->size + 1);
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
            res.size = res.cap;
        } else {
            res.size = res.cap - 1;
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
        res.cap = this->size;
        res.set_cap(res.cap);
        int ost = 0;
        for (int i = 0; i < that.size; i++)
        {
            if (that.value[i] > this->value[i] - ost)
            {
                res.value[i] = this->value[i] - ost + BASE - that.value[i];
                ost = 1;
            } else {
                res.value[i] = this->value[i] - ost - that.value[i];
                ost = 0;
            }
        }
        for (int i = that.size; i < this->size; i++)
        {
            if (this->value[i] - ost < 0)
            {
                res.value[i] = this->value[i] - ost + BASE;
                ost = 1;
            } else {
                res.value[i] = this->value[i] - ost;
                ost = 0;
            }
        }
        res.size = res.cap;
        res.delete0();
        res.sign = 1;
        return res;
    }
}
BigInt BigInt::num_mult(const int &value) const {
    BigInt res;
    res.set_cap(this->size + 1);
    int ost = 0;
    for (int i = 0; i < this->size; i++)
    {
        res.value[i] = (this->value[i] * value + ost) % BASE;
        ost = (this->value[i] * value + ost) / BASE;
    }
    if (ost > 0)
    {
        res.value[this->size] = ost;
        res.size = res.cap;
    } else {
        res.size = res.cap - 1;
    }
    res.sign = this->sign;
    return res;
}
BigInt BigInt::mult_by_10() const{
    BigInt res;
    res.set_cap(this->size + 1);
    int ost = 0;
    for (int i = 0; i < this->size; i++)
    {
        res.value[i] = (this->value[i] % (BASE / 10)) * 10 + ost;
        ost = this->value[i] / (BASE / 10);
    }
    res.value[this->size] = ost;
    res.size = res.cap;
    res.delete0();
    res.sign = this->sign;
    return res;
}
BigInt BigInt::mult_by_BASE_in_n(int n) const
{
    BigInt res;
    res.set_cap(this->size + n);
    res.size = res.cap;
    for (int i = 0; i < n; i++)
    {
        res.value[i] = 0;
    }
    for (int i = n; i < res.cap; i++)
    {
        res.value[i] = this->value[i - n];
    }
    res.sign = this->sign;
    return res;
}
BigInt BigInt::mult_by_10_in_n(int n) const
{
    BigInt res(this->mult_by_BASE_in_n(n / DIGIT_COUNT));
    for (int i = 0; i < n % DIGIT_COUNT; i++)
    {
        res = res.mult_by_10();
    }
    return res;
}
BigInt BigInt::division(const BigInt &that) const
{
    BigInt res;
    int k = 0;
    while (that.value[k] == 0)
    {
        k++;
    }
    BigInt newthat(that, that.size - k);
    newthat.sign = 1;
    BigInt newthis(*this, this->size - k);
    newthis.sign = 1;
    res.set_cap(newthis.size - newthat.size + 2);
    res.size = res.cap;
    for (int i = 0; i < res.size; i++)
    {
        res.value[i] = 0;
    }
    int i = newthis.size - 1;
    BigInt temp(0);
    int j = 0;
    while (i >= 0)
    {
        while (i >= 0 && (newthat > temp || newthat == temp)) {
            temp = temp.mult_by_BASE_in_n(1) + newthis.value[i];
            temp.delete0();
            //cout << "temp  " << temp;
            i--;
        }
        if (temp > newthat)
        {
            int base_res = 0;
            while (temp > newthat || (temp == newthat && i < 0))
            {
                temp -= newthat;
                base_res++;
            }
            //cout << "base res :" <<  base_res << endl;
            res.value[res.size - 2 - j] += base_res;
            j++;
        }
    }
    for (int i = res.size - 1 - j; i < res.size - 1; i++)
    {
        res.value[i + 1] += res.value[i] / BASE;
        res.value[i] = res.value[i] % BASE;
    }
    if (res.value[res.size - 1] > 0)
        j++;
    res.sign = this->sign * that.sign;
    res.delete0();
    BigInt result(res, j);
    return result;
}



//ПОТОКИ
ostream& operator<<(ostream& res, const BigInt &a)
{
    if (a.sign == -1 && a.value[a.size - 1] != 0)
        res << '-';
    for (int i = a.size - 1; i >= 0; i--)
    {
        int d = a.BASE / 10;
        int &v = a.value[i];
        while (i < a.size - 1 && d > v + 1)
        {
            res << '0';
            d /= 10;
        }
        int t = 9;
        for (int j = 0; j < BigInt::DIGIT_COUNT - 1; j++)
        {
            if (i < a.size - 1 && v == t)
            {
                cout << '0';
            }
            t = (t * 10 + 9);
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



//ПРИСВАИВАНИЕ
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



//СРАВНЕНИЕ
bool BigInt::operator>(const BigInt &that) const
{
    if (this->size < that.size || that == *this) {
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
    //cout << that;
    if (this->size != that.size)
    {
        return false;
    } else {
        bool flag = true;
        for (int i = 0; i < this->size; i++)
        {
            //cout << this->value[i] << " " << that.value[i] << endl;
            if (this->value[i] != that.value[i])
                flag = false;
        }
        //cout << flag << endl;
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



//+
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
BigInt &BigInt::operator+=(const BigInt &that)
{
    *this = *this + that;
    return *this;
}
BigInt &BigInt::operator+=(const int &value)
{
    *this = *this + value;
    return *this;
}
BigInt &BigInt::operator+=(const unsigned int &value)
{
    *this = *this + value;
    return *this;
}
BigInt &BigInt::operator+=(const long long &value)
{
    *this = *this + value;
    return *this;
}
BigInt &BigInt::operator+=(const unsigned long long &value)
{
    *this = *this + value;
    return *this;
}
BigInt &BigInt::operator++()
{
    *this = *this + 1;
    return *this;
}
BigInt BigInt::operator++(int)
{
    BigInt old(*this);
    ++*this;
    return old;
}


//-
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
BigInt &BigInt::operator-=(const BigInt &that)
{
    *this = *this - that;
    return *this;
}
BigInt &BigInt::operator-=(const int &value)
{
    *this = *this - value;
    return *this;
}
BigInt &BigInt::operator-=(const unsigned int &value)
{
    *this = *this - value;
    return *this;
}
BigInt &BigInt::operator-=(const long long &value)
{
    *this = *this - value;
    return *this;
}
BigInt &BigInt::operator-=(const unsigned long long &value)
{
    *this = *this - value;
    return *this;
}
BigInt &BigInt::operator--()
{
    *this = *this - 1;
    return *this;
}
BigInt BigInt::operator--(int)
{
    BigInt old(*this);
    --*this;
    return old;
}



//*
BigInt BigInt::operator*(const BigInt &that) const
{
    BigInt res(0);
    for (int i = 0; i < that.size; i++)
    {
        for (int j = 0; j < DIGIT_COUNT; j++)
        {
            res += (*this * (that.value[i] / int (pow(10, j)) % 10)).mult_by_10_in_n(i * DIGIT_COUNT + j);
        }
    }
    res.sign = this->sign * that.sign;
    return res;
}
BigInt BigInt::operator*(const int &value) const
{
    if (value >= 0 && value < 10)
    {
        return num_mult(value);
    }
    BigInt that(value);
    return *this * that;
}
BigInt BigInt::operator*(const unsigned int &value) const
{
    if (value < 10)
    {
        return num_mult(value);
    }
    BigInt that(value);
    return *this * that;
}
BigInt BigInt::operator*(const long long &value) const
{
    if (value >= 0 && value < 10)
    {
        return num_mult(int(value));
    }
    BigInt that(value);
    return *this * that;
}
BigInt BigInt::operator*(const unsigned long long &value) const
{
    if (value < 10)
    {
        return num_mult(int(value));
    }
    BigInt that(value);
    return *this * that;
}
BigInt &BigInt::operator*=(const BigInt &that)
{
    *this = *this * that;
    return *this;
}
BigInt &BigInt::operator*=(const int &value)
{
    *this = *this * value;
    return *this;
}
BigInt &BigInt::operator*=(const unsigned int &value)
{
    *this = *this * value;
    return *this;
}
BigInt &BigInt::operator*=(const long long &value)
{
    *this = *this * value;
    return *this;
}
BigInt &BigInt::operator*=(const unsigned long long &value)
{
    *this = *this * value;
    return *this;
}



//division
BigInt BigInt::operator/(const BigInt &that) const{
    //cout << that;
    if (that == BigInt(0))
    {
        throw BigIntegerDivisionByZero();
    } else {
        if (that > *this)
        {
            //cout << "qwerty" << endl;
            return BigInt(0);
        } else {
            if (that == *this)
            {
                //cout << "******** ";
                return BigInt(1);
            } else {
                return division(that);
            }
        }
    }
}
BigInt BigInt::operator/(const int &value) const
{
    BigInt that(value);
    return *this / that;
}
BigInt BigInt::operator/(const unsigned int &value) const
{
    BigInt that(value);
    return *this / that;
}
BigInt BigInt::operator/(const long long &value) const
{
    BigInt that(value);
    return *this / that;
}
BigInt BigInt::operator/(const unsigned long long &value) const
{
    BigInt that(value);
    return *this / that;
}
BigInt &BigInt::operator/=(const BigInt &that)
{
    *this = *this / that;
    return *this;
}
BigInt &BigInt::operator/=(const int &value)
{
    *this = *this / value;
    return *this;
}
BigInt &BigInt::operator/=(const unsigned int &value)
{
    *this = *this / value;
    return *this;
}
BigInt &BigInt::operator/=(const long long &value)
{
    *this = *this / value;
    return *this;
}
BigInt &BigInt::operator/=(const unsigned long long &value)
{
    *this = *this / value;
    return *this;
}

