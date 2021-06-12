#include "lib/lru_cache.h"
#include <iostream>
/*
ToDo:
- Iterators
- Benchmark it
- Write your own testing that can check it with large inputs
*/

template <typename Key, typename Value>
LRUCache<Key, Value>::LRUCache(size_t n) {
    threshold_ = n;
}

template <typename Key, typename Value>
LRUCache<Key, Value>::~LRUCache() {
}

template <typename Key, typename Value>
Value &LRUCache<Key, Value>::operator[](Key key) {
    return table_[key].value;
}

template <typename Key, typename Value>
void LRUCache<Key, Value>::Insert(Key key, Value value) {
    list_->Insert(value);
    // if (Empty()) {
    // }
    size_++;
}

template <typename Key, typename Value>
void LRUCache<Key, Value>::Erase(Key key) {
    size_--;
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

template <typename Key, typename Value>
Value LRUCache<Key, Value>::Peek() {
    return !Empty() ? list_->Peek() : 0;
}
