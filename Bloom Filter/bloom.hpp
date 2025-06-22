#pragma once

#include <bitset>
#include <string>
#include <utility>
#include <cmath>
#include <functional>
#include <stdexcept>

using namespace std;
constexpr size_t MAX_BITS = 16384;

class BloomFilter {
public:
    BloomFilter(size_t expectedElements, double falsePositiveRate);

    void add(const string &key);
    bool contains(const string &key) const;
    void clear();

    double estimateFalsePositiveRate() const;

    size_t bitSize()   const noexcept { return m_bits; }
    size_t hashCount() const noexcept { return k_hashes; }
    size_t elemCount() const noexcept { return count; }

private:
    size_t m_bits;               
    size_t k_hashes;             
    size_t count = 0;           
    bitset<MAX_BITS> bit_array; 

    static pair<uint64_t,uint64_t> hashPair(const string &s);
};
