#pragma once

#include <unordered_map>

#include "../src/doubly_linked_list.cpp"

template <typename Key, typename Value>
class LRUCache {
public:
    LRUCache(size_t n);
    ~LRUCache();
	Value &operator[](Key key);
    // If same key is already present, it will be updated with new value
	void Insert(Key key, Value valu);
	void Erase(Key key);
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
        Data(){
            node = nullptr;
        }
    };

    std::unordered_map<Key, Data> table_;

    DoublyLinkedList<Value> *list_;
};