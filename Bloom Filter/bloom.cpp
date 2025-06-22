#include "bloom.hpp"

BloomFilter::BloomFilter(size_t expectedElements, double falsePositiveRate) {
    if (expectedElements == 0 || falsePositiveRate <= 0.0 || falsePositiveRate >= 1.0)
        throw invalid_argument("BloomFilter: invalid parameters");

    // m = -(n * ln p) / (ln 2)^2
    /*
    
    m = number of expected bits for given data
    n = total number of expected elements to insert
    p = expected false positive rate

    */
    double num = -static_cast<double>(expectedElements) * log(falsePositiveRate);
    double den = pow(log(2.0), 2);
    m_bits = static_cast<size_t>(ceil(num / den));

    if (m_bits > MAX_BITS)
        throw invalid_argument("BloomFilter: MAX_BITS too small for desired parameters");

    // k = (m / n) * ln 2

    /*
    
    k = number of hashes
    
    */

    k_hashes = static_cast<size_t>(round((static_cast<double>(m_bits) / expectedElements) * log(2.0)));
    if (k_hashes == 0) k_hashes = 1;
}

void BloomFilter::add(const string &key) {
    pair<uint64_t,uint64_t> hp = hashPair(key);
    uint64_t h1 = hp.first;
    uint64_t h2 = hp.second;
    for (size_t i = 0; i < k_hashes; ++i) {
        size_t idx = (h1 + i * h2) % m_bits;
        bit_array.set(idx);
    }
    ++count;
}

bool BloomFilter::contains(const string &key) const {
    pair<uint64_t,uint64_t> hp = hashPair(key);
    uint64_t h1 = hp.first;
    uint64_t h2 = hp.second;
    for (size_t i = 0; i < k_hashes; ++i) {
        size_t idx = (h1 + i * h2) % m_bits;
        if (!bit_array.test(idx))
            return false;
    }
    return true;
}

void BloomFilter::clear() {
    bit_array.reset();
    count = 0;
}

double BloomFilter::estimateFalsePositiveRate() const {
    // (1 - e^{-k * count / m})^k
    /*
        count = number of elements inserted
    */
    double exp_part = exp(-static_cast<double>(k_hashes) * count / m_bits);
    return pow(1.0 - exp_part, k_hashes);
}

pair<uint64_t,uint64_t> BloomFilter::hashPair(const string &s) {
    uint64_t h1 = hash<string>{}(s);
    uint64_t h2 = hash<uint64_t>{}(h1);
    return {h1, h2};
}
