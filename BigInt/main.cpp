//
//  main.cpp
//  BigInt
//
//  Created by Alexey Karpov on 14.03.17.
//  Copyright © 2017 Alexey Karpov. All rights reserved.
//

#include <iostream>
#include "BigInt.hpp"

using namespace std;

int main() {
    unsigned long long value = 1847;
    BigInt a(value);
    BigInt b("-8655");
    cout << b;
    a *= b;
    cout << a;
    return 0;
}
