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

using namespace std;

class BigInt {
private:
    const int BASE = 1000;
    const int DIGIT_COUNT = 3;
    int cap;
    int *value;
    void set_cap (const int cap);
    void assign(const char *);
    void assign(const BigInt &that);
    void assign(int &value);
public:
    BigInt(int &value);
    BigInt(char *str);
    BigInt(const BigInt &that);
    ~BigInt();
    void print();
    friend istream& operator>>(istream& in, BigInt &a);
    friend ostream& operator<<(ostream& res, const BigInt &a);
    BigInt &operator=(const BigInt &that);
    BigInt &operator=(const char *);
    BigInt &operator=(int &value);
};

#endif /* BigInt_hpp */

