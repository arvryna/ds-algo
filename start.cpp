#include<iostream>
#include "src/lru_cache.cpp"

int main() {
    LRUCache<std::string, int> cache(10);
    cache.Insert("ProductID-123", 10);
    std::cout << cache["Orange"] << std::endl;
    cache.Clear();
    return 0;
}