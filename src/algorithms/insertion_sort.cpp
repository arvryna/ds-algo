/*
  Implementation of insertion sort
  Copyright 2021 <arv>
*/

#include <iostream>
#include <vector>

std::vector<int> ReadInputFromUser(size_t n) {
    std::vector<int> list(n);
    for (size_t i = 0; i < list.size(); ++i) {
        int val;
        std::cin >> val;
        list[i] = val;
    }
    return list;
}

void PerformInsertionSort(std::vector<int> &list) {
    for (size_t i = 0; i < list.size(); ++i) {
        for (size_t j = i; j > 0; j--) {
            if (list[j] < list[j - 1]) {
                std::swap(list[j], list[j - 1]);
            }
        }
    }
}

void PrintSortedList(const std::vector<int> &list) {
    for (auto val : list) {
        std::cout << val << " ";
    }
}

int main() {
    size_t n;
    std::cin >> n;
    std::vector<int> list = ReadInputFromUser(n);
    PerformInsertionSort(list);
    PrintSortedList(list);
    return 0;
}
