#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <string>
#include <cmath>
#include <stdexcept>
#include "vector.h"
#include "my_hash.h"
#include <iostream>

// Counting Bloom Filter
class BloomFilter {
public:
    BloomFilter(long long n, double p); // n - предположительное количество элементов, p - предполагаемая вероятность ложного срабатывания

    void insert(const std::string& key);
    void remove(const std::string& key);
    bool contains(const std::string& key) const;

private:
    size_t m; // size
    size_t k; // count of hash funcs
    Vector<int> counters;
};

BloomFilter::BloomFilter(long long n, double p) {
    if (p <= 0 || p >= 1) {
        throw std::invalid_argument("Probability must be between 0 and 1");
    }

    // m and k
    double m_calculated = -n * std::log(p) / (std::log(2) * std::log(2));
    m = static_cast<size_t>(m_calculated);

    k = static_cast<size_t>((m / n) * std::log(2));

    // Init int counters
    counters.resize(m);
    for (size_t i = 0; i < m; i++) {
        counters.set(i, 0);
    }
}

void BloomFilter::insert(const std::string& key) {
    for (size_t i = 0; i < k; ++i) {
        size_t hash_value = my_hash(key, i) % m;
        counters.set(hash_value, counters.get(hash_value) + 1);
    }
}

void BloomFilter::remove(const std::string& key) {
    for (size_t i = 0; i < k; ++i) {
        size_t hash_value = my_hash(key, i) % m;
        if (counters.get(hash_value) > 0) {
            counters.set(hash_value, counters.get(hash_value) - 1);
        }
    }
}

bool BloomFilter::contains(const std::string& key) const {
    for (size_t i = 0; i < k; ++i) {
        size_t hash_value = my_hash(key, i) % m;
        if (counters.get(hash_value) == 0) {
            return false;
        }
    }
    return true;
}

#endif // BLOOM_FILTER_H
