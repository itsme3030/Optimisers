#include "bloom.cpp"
#include <iostream>
using namespace std;

int main() {
    /*
    
    1000 insert
    1% false positive rate
    
    */
    BloomFilter bf(1000, 0.01);

    bf.add("apple");
    bf.add("banana");

    cout << boolalpha;
    cout << "Contains 'apple'? "  << bf.contains("apple")  << "\n"; 
    cout << "Contains 'grape'? "  << bf.contains("grape")  << "\n"; 
    cout << "Contains 'apple'? "  << bf.contains("apple")  << "\n";
    cout << "Bit array size: "     << bf.bitSize()   << "\n";
    cout << "Hash functions: "     << bf.hashCount() << "\n";
    cout << "Elements added: "     << bf.elemCount() << "\n";
    cout << "Est. FPR: "           << bf.estimateFalsePositiveRate() << "\n";

    return 0;
}
