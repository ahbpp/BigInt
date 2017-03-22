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

using namespace std;

class BigInt {
private:
    const unsigned int BASE = 1000;
    const unsigned int DIGIT_COUNT = 3;
    int size;
    int cap;
    int *value;
    int sign;
    
    void set_cap (const int cap);
    void assign(const char *);
    void assign(const BigInt &that);
    void assign(int value);
    void assign(unsigned int value);
    void assign(long long value);
    void assign(unsigned long long value);
    void delete0();
    
    BigInt abs_sum(const BigInt &that) const;
    BigInt abs_minus(const BigInt &that) const;
    BigInt num_mult(const int &value) const;
    BigInt mult_by_10() const;
    BigInt mult_by_BASE_in_n(int n) const;
    BigInt mult_by_10_in_n(int n) const;
    
    BigInt();
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

    
    bool operator>(const BigInt &that) const;
    bool operator<(const BigInt &that) const;
    bool operator==(const BigInt &that) const;
    
    
};

#endif /* BigInt_hpp */

