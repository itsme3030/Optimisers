#include "hyperloglog.hpp"
#include <cmath>
#include <algorithm>   

HyperLogLog::HyperLogLog(uint8_t b)
  : bits(b), m(size_t(1) << b), regs(m, 0)
{
    if (b < 4 || b > 16)
        throw invalid_argument("HyperLogLog: b must be between 4 and 16");
}

uint32_t HyperLogLog::hash32(const string& s) {
    return static_cast<uint32_t>(hash<string>{}(s));
}

uint8_t HyperLogLog::trailingZeros(uint32_t x, uint8_t maxBits) {
    if (x == 0) 
        return maxBits + 1;
    return static_cast<uint8_t>(__builtin_ctz(x)) + 1;
}

void HyperLogLog::add(const string& item) {
    uint32_t h     = hash32(item);
    uint32_t idx   = h >> (32 - bits);
    uint32_t low   = h & ((uint32_t(1) << (32 - bits)) - 1);
    uint8_t  rank  = trailingZeros(low, 32 - bits);
    regs[idx]   = max(regs[idx], rank);
}

double HyperLogLog::estimate() const {
    double sum = 0.0;
    for (auto r : regs)
        sum += 1.0 / (1u << r);

    double raw = alphaMM() / sum;

    if (raw <= 2.5 * m) {
        size_t V = count(regs.begin(), regs.end(), 0);
        if (V > 0)
            raw = m * log(static_cast<double>(m) / V);
    }
    return raw;
}

double HyperLogLog::alphaMM() const {
    switch (m) {
      case 16:  return 0.673 * m * m;
      case 32:  return 0.697 * m * m;
      case 64:  return 0.709 * m * m;
      default:  return (0.7213 / (1.0 + 1.079 / m)) * m * m;
    }
}

void HyperLogLog::clear() {
    fill(regs.begin(), regs.end(), 0);
}

size_t HyperLogLog::registerCount() const {
    return m;
}
