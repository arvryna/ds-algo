#include <iostream>

#include "src/lru_cache.cpp"

void Assert(const std::string &title, const std::string &expected, const std::string &got) {
    std::cout << "[" + title + "]";
    if (expected == got) {
        std::cout << ": Passed ✅" << std::endl;
    } else {
        std::cout << ": Failed ❌";
        std::cout << " (Expected :" + expected + " Got: " + got +")"<< std::endl;
    }
}

void TestLRUCache() {
    std::cout << "Testing LRU Cache" << std::endl;
    LRUCache<std::string, int> cache(3);
    cache.Clear();
    Assert("check empty state", "0", "0");
    
    cache.Insert("red", 10);

    Assert("check insert", "10", std::to_string(cache["red"]));
    
    cache.Insert("red", 20);
    cache.Insert("blue", 30);
    cache.Insert("orange", 40);
    cache.Insert("green", 50);

    Assert("check size", "3", std::to_string(cache.Size()));
    Assert("check head", "50", std::to_string(cache.Peek()));

    cache.Insert("ProductID-123", 10);
    cache.Clear();
}

int main() {
    TestLRUCache();
    return 0;
}