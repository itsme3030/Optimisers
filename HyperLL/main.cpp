#include "hyperloglog.cpp"
#include <iostream>
#include<bits/stdc++.h>
using namespace std;

int main() {
    /* 2^10 = 1024 registers → ~3.2% standard error */
    HyperLogLog hll(10);
    map<string,int> actual;

    for (int i = 0; i < 10000; ++i) {
        hll.add("user_" + to_string(i));
    }

    cout << "Registers (m): "   << hll.registerCount() << "\n";
    cout << "Estimate: "        << hll.estimate()      << "\n";
    cout << "Actual: "          << 10000     << "\n";


    hll.clear();
    for(int i = 0; i < 10000; i++) {
        string dum = to_string(rand() * 1000);
        hll.add(dum);
        actual[dum]++;
    }
    cout << "Estimate: "        << hll.estimate()      << "\n";
    cout << "Actual: "        << (int)actual.size()      << "\n";

    return 0;
}
