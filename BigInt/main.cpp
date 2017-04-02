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
    char stra[10002];
    cin >> stra;
    BigInt a(stra);
    BigInt c(a.sqrt());
    cout << c;
    return 0;
}
