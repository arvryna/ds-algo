#ifndef lru_cache_h
#define lru_cache_h

#include <unordered_map>

#include "containers/linked_list.h"

template <typename Key, typename Value>
class LRUCache {
public:
    LRUCache(size_t n);
	Value &operator[](Key key);
	bool Delete(Key key);
	bool Empty();
    void Clear();
	Value Peek(); // Returns the head of the cache
    size_t Size();

private:
    size_t size_;
    size_t threshold_;

    struct Data {
        Value value;
        DoublyLinkedList<Value> *node;
    };

    std::unordered_map<Key, Data> table_;
};

#endif /* lru_cache_h */