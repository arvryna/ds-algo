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
    Clear();
}

template <typename Key, typename Value>
Value &LRUCache<Key, Value>::operator[](Key key) {
    // For every access, promote that node to come to head
    return table_[key].value;
}

template <typename Key, typename Value>
void LRUCache<Key, Value>::Insert(Key key, Value value) {
    if(size_ == threshold_){
        //Erase low priority node
        // list_->Erase(table_[key].node);

        // Insert new node and treat it as high priority
    }else{
        // Delete tail
        // list_->Insert(value);
        table_[key] = Data(value);
        size_++;
    }
}

template <typename Key, typename Value>
void LRUCache<Key, Value>::Erase(Key key) {
    table_.erase(key);
    //remove from linkedlist
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
    // list_->Clear();
    // delete list_;
}

template <typename Key, typename Value>
Value LRUCache<Key, Value>::Peek() {
    // return !Empty() ? list_->Peek() : 0;
    return 0;
}
