//
//  BigInt.hpp
//  BigInt
//
//  Created by Alexey Karpov on 14.03.17.
//  Copyright © 2017 Alexey Karpov. All rights reserved.
//

#ifndef BigInt_hpp
#define BigInt_hpp

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <stdlib.h>
#include <cstring>

using namespace std;

class BigInt {
private:
    static const int BASE = 10000;
    static const int DIGIT_COUNT = 4;
    int size;
    int cap;
    int *value;
    int sign;
    
    void set_cap (const int cap);
    void assign(const char *);
    void assign(const BigInt &that);
    void assign(const BigInt &that, const int n);
    void assign(int value);
    void assign(unsigned int value);
    void assign(long long value);
    void assign(unsigned long long value);
    void reduce_size();
    
    BigInt abs_sum(const BigInt &that) const;
    BigInt abs_minus(const BigInt &that) const;
    BigInt num_mult(const int &value) const;
    BigInt mult_by_10() const;
    BigInt mult_by_BASE_in_n(int n) const;
    BigInt mult_by_10_in_n(int n) const;
    BigInt division(const BigInt &that) const;
    
    bool operator>(const BigInt &that) const;
    bool operator<(const BigInt &that) const;
    bool operator==(const BigInt &that) const;
    
    BigInt();
    BigInt(const BigInt &that, const int n);
public:
    BigInt(const int &value);
    BigInt(const unsigned int &value);
    BigInt(const long long &value);
    BigInt(const unsigned long long &value);
    BigInt(char *str);
    BigInt(const BigInt &that);
    ~BigInt();
    
    friend istream& operator>>(istream& in, BigInt &a);
    friend ostream& operator<<(ostream& res, const BigInt &a);
    
    BigInt &operator=(const BigInt &that);
    BigInt &operator=(const char *);
    BigInt &operator=(int value);
    
    BigInt operator+(const BigInt &that) const;
    BigInt operator+(const int &value) const;
    BigInt operator+(const unsigned int &value) const;
    BigInt operator+(const long long &value) const;
    BigInt operator+(const unsigned long long &value) const;
    BigInt &operator+=(const BigInt &that);
    BigInt &operator+=(const int &value);
    BigInt &operator+=(const unsigned int &value);
    BigInt &operator+=(const long long &value);
    BigInt &operator+=(const unsigned long long &value);
    BigInt &operator++();
    BigInt operator++(int);
    
    BigInt operator-(const BigInt &that) const;
    BigInt operator-(const int &value) const;
    BigInt operator-(const unsigned int &value) const;
    BigInt operator-(const long long &value) const;
    BigInt operator-(const unsigned long long &value) const;
    BigInt &operator-=(const BigInt &that);
    BigInt &operator-=(const int &value);
    BigInt &operator-=(const unsigned int &value);
    BigInt &operator-=(const long long &value);
    BigInt &operator-=(const unsigned long long &value);
    BigInt &operator--();
    BigInt operator--(int);
    
    BigInt operator*(const BigInt &that) const;
    BigInt operator*(const int &value) const;
    BigInt operator*(const unsigned int &value) const;
    BigInt operator*(const long long &value) const;
    BigInt operator*(const unsigned long long &value) const;
    BigInt &operator*=(const BigInt &that);
    BigInt &operator*=(const int &value);
    BigInt &operator*=(const unsigned int &value);
    BigInt &operator*=(const long long &value);
    BigInt &operator*=(const unsigned long long &value);
    
    BigInt operator/(const BigInt &that) const;
    BigInt operator/(const int &value) const;
    BigInt operator/(const unsigned int &value) const;
    BigInt operator/(const long long &value) const;
    BigInt operator/(const unsigned long long &value) const;
    BigInt &operator/=(const BigInt &that);
    BigInt &operator/=(const int &value);
    BigInt &operator/=(const unsigned int &value);
    BigInt &operator/=(const long long &value);
    BigInt &operator/=(const unsigned long long &value);
    BigInt nod(const BigInt &that) const;
    BigInt sqrt() const;
};

class BigIntegerDivisionByZero : logic_error {
public:
    BigIntegerDivisionByZero();
};
class BigIntegerOverflow : overflow_error {
public:
    BigIntegerOverflow();
};

#endif /* BigInt_hpp */

