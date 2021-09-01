#include <iostream>
#include <map>
#include <vector>

template <typename ElementType, typename Compare = std::less<ElementType>>
class Heap {
public:
    explicit Heap(Compare comp = Compare()) : comp_{comp} {
    }

    // Build a heap in O(n) time from a vector
    void MakeHeap(const std::vector<ElementType>& array) {
        element_to_index_.clear();
        for (size_t i = 0; i < array.size(); i++) {
            element_to_index_[array[i]] = i;
        }

        heap_ = array;
        for (int i = (heap_.size() - 1) / 2; i >= 0; --i) {
            SiftDown(i);
        }
    }

    void Insert(const ElementType& element) {
        heap_.push_back(element);
        element_to_index_[element] = heap_.size() - 1;
        SiftUp(heap_.size() - 1);
    }

    // Delete and return the minimum element from heap
    ElementType RemoveMin() {
        ElementType res = heap_[0];
        std::swap(element_to_index_[heap_[0]], element_to_index_[heap_[heap_.size() - 1]]);
        std::swap(heap_[0], heap_[heap_.size() - 1]);

        // Delete the elements
        heap_.pop_back();
        element_to_index_.erase(res);

        SiftDown(0);
        return res;
    }

    // Return the minimum element from heap
    const ElementType& GetMin() const {
        return heap_[0];
    }

    // Change old_element to new_element in heap, and fix heap property
    void ChangeKey(const ElementType& old_element, const ElementType& new_element) {
        size_t index = element_to_index_[old_element];
        // Update heap
        heap_[index] = new_element;

        // Update map
        element_to_index_.erase(old_element);
        element_to_index_[new_element] = index;

        // Clear violations
        SiftUp(index);
    }

    void PrintHeap() {
        for (size_t i = 0; i < heap_.size(); ++i) {
            std::cout << heap_[i] << " ";
        }

        std::cout << "map=";
        for (const auto& x : element_to_index_) {
            std::cout << x.first << ":" << x.second << ", ";
        }
    }

private:
    // Push the element in position index up
    void SiftUp(size_t index) {
        while (index != 0) {
            size_t parent = GetParent(index);
            if (heap_[index] < heap_[parent]) {
                std::swap(element_to_index_[heap_[index]], element_to_index_[heap_[parent]]);
                std::swap(heap_[index], heap_[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    // Push the element in position index down
    void SiftDown(size_t index) {
        while (ShouldSiftDown(index)) {
            size_t new_index = 0;
            size_t left_son = GetLeftChild(index);
            size_t right_son = GetRightChild(index);
            if (HasLeftChild(index) && HasRightChild(index)) {
                new_index = (heap_[left_son] < heap_[right_son]) ? left_son : right_son;
            } else if (HasLeftChild(index)) {
                new_index = (heap_[index] > heap_[left_son]) ? left_son : new_index;
            } else if (HasRightChild(index)) {
                new_index = (heap_[index] > heap_[right_son]) ? right_son : new_index;
            }
            std::swap(element_to_index_[heap_[index]], element_to_index_[heap_[new_index]]);
            std::swap(heap_[index], heap_[new_index]);
            index = new_index;
        }
    }

    bool ShouldSiftDown(size_t index) {
        if (HasLeftChild(index) && (heap_[index] > heap_[GetLeftChild(index)])) {
            return true;
        } else if (HasRightChild(index) && (heap_[index] > heap_[GetRightChild(index)])) {
            return true;
        }
        return false;
    }

    // Change the element in position index with a new one and restore the heap property
    void DecreaseKey(size_t index, const ElementType& new_value) {
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

    bool HasLeftChild(size_t index) const {
        return 2 * index + 1 < heap_.size();
    }

    bool HasRightChild(size_t index) const {
        return 2 * index + 2 < heap_.size();
    }

private:
    std::map<ElementType, size_t, Compare> element_to_index_;
    std::vector<ElementType> heap_;
    Compare comp_;
};

std::vector<int> GetElementsForHeap() {
    size_t n;
    std::cin >> n;
    std::vector<int> elements(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> elements[i];
    }
    return elements;
}

void HeapInterfaceTester() {
    int n;
    std::cin >> n;
    Heap<int> heap;
    for (int i = 0; i < n; i++) {
        std::string cmd;
        std::cin >> cmd;
        if (cmd == "Insert") {
            int val;
            std::cin >> val;
            heap.Insert(val);
            std::cout << val << std::endl;
        } else if (cmd == "GetMin") {
            std::cout << heap.GetMin() << std::endl;
        } else if (cmd == "ChangeKey") {
            int old_element;
            int new_element;
            std::cin >> old_element >> new_element;
            heap.ChangeKey(old_element, new_element);
            std::cout << "ChangeKey" << std::endl;
        } else if (cmd == "MakeHeap") {
            heap.MakeHeap(GetElementsForHeap());
            std::cout << "MakeHeap" << std::endl;
        } else if (cmd == "RemoveMin") {
            std::cout << heap.RemoveMin() << std::endl;
        } else if (cmd == "PrintHeap") {
            heap.PrintHeap();
        }
    }
}

int main() {
    HeapInterfaceTester();
    return 0;
}
