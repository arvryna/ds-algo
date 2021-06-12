
#include "lib/bloom_filter.h"

#include <iostream>

/*
SPEC
****
use uniformly distributed hash function for BloomFilter
*/

template <typename Key, typename Value>
BloomFilter<Key, Value>::BloomFilter(const size_t n) {
}

template <typename Key, typename Value>
size_t BloomFilter<Key, Value>::Size() {
    return size_;
}