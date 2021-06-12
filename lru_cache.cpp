#include "lru_cache.h"

#include <iostream>
/*
ToDo:
- Iterators
- Import your own linked list and use it
- Benchmark it
- Write your own testing that can check it with large inputs
*/

template <typename Key, typename Value>
LRUCache<Key, Value>::LRUCache(size_t n) {
    threshold_ = n;
}

// template <typename Key, typename Value>
// LRUCache<Key, Value>::~LRUCache() {
// }

template <typename Key, typename Value>
Value &LRUCache<Key, Value>::operator[](Key key) {
    return table_[key].value;
}

template <typename Key, typename Value>
bool LRUCache<Key, Value>::Delete(Key key) {
    return true;
}

template <typename Key, typename Value>
size_t LRUCache<Key, Value>::Size() {
    return size_;
}

template <typename Key, typename Value>
bool LRUCache<Key, Value>::Empty() {
    return (size_ == 0);
}

template <typename Key, typename Value>
void LRUCache<Key, Value>::Clear() {
    size_ = 0;
    table_.clear();
}

// // return element on the top
// // Value peek(){
// //     return table_[].value;
// // }

int main() {
    LRUCache<std::string, int> cache(10);
    cache["Red"] = 100;
    std::cout << cache["Orange"] << std::endl;
    return 0;
}
