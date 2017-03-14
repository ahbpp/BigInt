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
    int value = 2345678;
    BigInt a(value);
    cin >> a;
    a.print();
    char str[] = "123400000000056789";
    BigInt b(str);
    b.print();
    BigInt c(b);
    cout << c;
    return 0;
}
