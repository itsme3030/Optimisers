#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>
using namespace std;
class HyperLogLog {
public:
    explicit HyperLogLog(uint8_t b = 10);
    void add(const string& item);
    double estimate() const;
    void clear();
    size_t registerCount() const;

private:
    uint8_t           bits;    
    size_t            m;       
    vector<uint8_t>   regs;    // max trailing-zero count per bucket
    static uint32_t   hash32(const string& s);
    static uint8_t    trailingZeros(uint32_t x, uint8_t maxBits);
    double            alphaMM() const;
};
