#include <iostream>
#include <unordered_map>

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
    Value &operator[](Key key) {
        return 0;
    }

private:

};

int main() {
    LRUCache<int, int> cache;
    cache[10] = 100;
    //     cache[10] = 10;
    return 0;
}
