/* Implementation of Quicksort */

#include <iostream>
#include <vector>

template <typename T>
struct CustomComparator {
    bool operator()(const T& lhs, const T& rhs) {
        return lhs <= rhs;
    }
};

template <typename T, typename Compare = CustomComparator<T>>
int SelectPivot(std::vector<T>& vec, int left, int right, Compare comp = Compare()) {
    return right;
}

template <typename T, typename Compare = CustomComparator<T>>
int Partition(std::vector<T>& vec, int left, int right, Compare comp = Compare()) {
    T pivot = vec[SelectPivot(vec, left, right)];
    int i = left - 1;
    for (int j = left; j <= right - 1; ++j) {
        if (comp(vec[j], pivot)) {
            ++i;
            std::swap(vec[i], vec[j]);
        }
    }
    std::swap(vec[i + 1], vec[right]);
    return i + 1;
}

template <typename T, typename Compare = CustomComparator<T>>
void Sort(std::vector<T>& vec, int left, int right, Compare comp = Compare()) {
    if (left < right) {
        int pi = Partition(vec, left, right);
        Sort(vec, left, pi - 1);
        Sort(vec, pi + 1, right);
    }
}

template <typename T>
void PrintList(const std::vector<T>& list) {
    for (size_t i = 0; i < list.size(); ++i) {
        std::cout << list[i] << " ";
    }
}

std::vector<int> ReadUserInput() {
    size_t n;
    std::cin >> n;
    std::vector<int> list(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> list[i];
    }
    return list;
}

int main() {
    std::vector<int> vec = ReadUserInput();
    Sort(vec, 0, vec.size() - 1);
    PrintList(vec);
    return 0;
}
