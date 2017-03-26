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
    char stra[10002], strb[10002];
    cin >> stra >> strb;
    BigInt a(stra), b(strb);
    cout << a << " " << b;
    cout << a / b << " " << a - ((a / b) * b);
    return 0;
}
