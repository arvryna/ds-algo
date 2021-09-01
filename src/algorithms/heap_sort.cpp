#include <iostream>
#include <vector>

template <typename T, typename Compare = std::greater<T>>
class HeapSort {
public:
    explicit HeapSort(Compare comp = Compare()) : comp_{comp} {
    }

    // Function get a vector by reference and sort it.
    void operator()(std::vector<T>& array) {
        MakeHeap(array);
        size_t heap_size = array.size();
        while (heap_size > 0) {
            std::swap(array[0], array[heap_size - 1]);
            --heap_size;
            SiftDown(array, 0, heap_size);
        }
    }

private:
    // Make a heap on an array in O(n)
    void MakeHeap(std::vector<T>& array) {
        for (int i = (array.size() - 1) / 2; i >= 0; --i) {
            SiftDown(array, i, array.size());
        }
    }

    void SiftDown(std::vector<T>& array, size_t index, size_t heap_size) {
        while (ShouldSiftDown(array, index, heap_size)) {
            size_t new_index = 0;
            size_t left_son = GetLeftChild(index);
            size_t right_son = GetRightChild(index);
            if (HasLeftChild(index, heap_size) && HasRightChild(index, heap_size)) {
                new_index = (array[left_son] > array[right_son]) ? left_son : right_son;
            } else if (HasLeftChild(index, heap_size)) {
                new_index = (array[index] < array[left_son]) ? left_son : new_index;
            } else if (HasRightChild(index, heap_size)) {
                new_index = (array[index] < array[right_son]) ? right_son : new_index;
            }
            std::swap(array[index], array[new_index]);
            index = new_index;
        }
    }

    bool ShouldSiftDown(std::vector<T>& array, size_t index, size_t heap_size) {
        if (HasLeftChild(index, heap_size) && (array[index] < array[GetLeftChild(index)])) {
            return true;
        } else if (HasRightChild(index, heap_size) &&
                   (array[index] < array[GetRightChild(index)])) {
            return true;
        }
        return false;
    }

    size_t GetLeftChild(size_t index) const {
        return 2 * index + 1;
    }

    size_t GetRightChild(size_t index) const {
        return 2 * index + 2;
    }

    size_t GetParent(size_t index) const {
        return (index + 1) / 2 - 1;
    }

    bool HasLeftChild(size_t index, size_t heap_size) const {
        return 2 * index + 1 < heap_size;
    }

    bool HasRightChild(size_t index, size_t heap_size) const {
        return 2 * index + 2 < heap_size;
    }

private:
    Compare comp_;
};

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
    HeapSort<int> heap;
    std::vector<int> list = ReadUserInput();
    heap(list);
    PrintList(list);
    return 0;
}
