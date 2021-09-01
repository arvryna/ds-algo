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

    bool Contains(Key key);
    size_t Size();
	Value Peek(); // Returns the head of the cache
    Value GetKthElement(Key index);
	bool Empty();
    void Clear();

private:
    size_t size_;
    size_t threshold_;
    struct Data {
        Value value;
        typename DoublyLinkedList<Value>::Node *node;
        Data(){
            node = nullptr;
        }
        Data(Value val){
            value = val;
            node = nullptr;
        }
        // Data(Value val, Node *new_node){
        //     node = new_node;
        //     value = val;
        // }
    };

    std::unordered_map<Key, Data> table_;
    DoublyLinkedList<Value> list_;
};