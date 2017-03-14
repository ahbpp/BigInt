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
    this->cap = cap;
    this->value = new int [this->cap];
}
BigInt::BigInt(int &value)
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
void BigInt::print()
{
    cout << "CAP:" << this->cap << endl;
    int n = 0;
    for (int i = this->cap - 1; i >= 0; i--)
    {
        cout << value[i] << " ";
        n++;
    }
    cout << endl << n << endl;
}

ostream& operator<<(ostream& res, const BigInt &a)
{
    for (int i = a.cap - 1; i >= 0; i--)
    {
        int d = a.BASE / 10;
        int &v = a.value[i];
        while (i < a.cap - 1 && d > v + 1) {
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

void BigInt::assign(const char *str)
{
    int len = strlen(str);
    set_cap((len - 1) / DIGIT_COUNT + 1);
    for (int i  = 0; i < this->cap; ++i) {
        value[i] = 0;
        for (int j = len - (i + 1) * DIGIT_COUNT; j < len - (i) * DIGIT_COUNT; j++) {
            if (j >= 0)
            {
                value[i] = (value[i] * 10) + (str[j] - '0');
            }
        }
    }
}
void BigInt::assign(const BigInt &that)
{
    set_cap(that.cap);
    for (int i = 0; i < this->cap; i++)
    {
        this->value[i] = that.value[i];
    }
}
void BigInt::assign(int &value)
{
    int v = BASE;
    int n = 1;
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
BigInt &BigInt::operator=(int &value)
{
    delete [] this->value;
    assign(value);
    return *this;
}
