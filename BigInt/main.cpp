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
    int value = 2;
    BigInt a(value);
    for (int i = 0; i < 10; i++)
    {
        a *= 2;
        cout << a;
    }
    a /= 33;
    cout << a--;
    cout << a;
    return 0;
}
