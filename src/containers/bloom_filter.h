#pragma once
#include <vector>

template <typename Key, typename Value>
class BloomFilter {
public:
    BloomFilter(const size_t n);
    Value &operator[](Key key);
    bool Delete(Key key);
    bool Empty();
    void Clear();
    Value Peek();  // Returns the head of the cache
    size_t Size();
    void Print();

private:
    size_t size_;
    std::vector<bool> elements_;
};
