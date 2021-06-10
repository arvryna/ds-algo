#include <iostream>
#include <unordered_map>

#include "containers/linked_list.h"

/*
ToDo:
- Iterators
- Setters getters
- Import your own linked list and use it
- Benchmark it
- Write your own testing that can check it with large inputs
*/

template <typename Key, typename Value>
class LRUCache {
public:
    explicit LRUCache(size_t n = 10) {
        threshold_ = n;
    }

    ~LRUCache() {
        // Free linked list
    }

    Value &operator[](Key key) {
        return table_[key].value;
    }

    void Clear() {
        size_ = 0;
        table_.clear();
    }

    // return element on the top
    // Value peek(){
    //     return table_[].value;
    // }

private:
    struct Node {};
    struct Data {
        Value value;
        Node *node;
    };

    std::unordered_map<Key, Data> table_;
    size_t size_;
    size_t threshold_;
};

int main() {
    LRUCache<int, int> cache(10);
    cache[10] = 100;
    //     cache[10] = 10;
    return 0;
}
