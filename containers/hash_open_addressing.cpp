#include <functional>
#include <iostream>
#include <vector>

template <typename Key, typename T, typename Hash = std::hash<Key>,
          typename KeyEqual = std::equal_to<Key>>
class HashTable {

private:
    struct Item;
    enum class HashState;

public:
    /*
     * See https://en.cppreference.com/w/cpp/named_req/ForwardIterator.
     */
    class Iterator : public std::iterator<std::forward_iterator_tag, std::pair<Key, T>> {

    public:
        Iterator(HashTable* table, size_t index) {
            table_ = table;
            index_ = (table->items_.size() == 1) ? FindNextItemIndex(index) : index;
        }

        bool operator==(const Iterator& rhs) const {
            return table_ == rhs.table_ && index_ == table_->items_.size();
        }

        bool operator!=(const Iterator& rhs) const {
            return !(*this == rhs);
        }

        Iterator& operator++() {
            index_++;
            size_t size = table_->items_.size();
            index_ = (index_ < size) ? FindNextItemIndex(index_) : index_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator copy(*this);
            operator++();
            return copy;
        }

        std::pair<Key, T>& operator*() {
            return table_->items_[index_].pair;
        }

        std::pair<Key, T>* operator->() {
            return &table_->items_[index_].pair;
        };

    private:
        // Returns the index of the next Occupied item from the given index
        size_t FindNextItemIndex(size_t index) {
            Item item = table_->items_[index];
            if (item.state != HashState::Occupied) {
                for (; index < table_->items_.size(); ++index) {
                    item = table_->items_[index];
                    if (item.state == HashState::Occupied) {
                        break;
                    }
                }
            }
            return index;
        }

    private:
        HashTable* table_;
        size_t index_;
        std::pair<Key, T> pair_;
    };

    /*
     * See https://en.cppreference.com/w/cpp/container/unordered_map/unordered_map (1)
     */
    HashTable() {
        items_.resize(kInitialBucketSize);
    }

    /*
     * See https://en.cppreference.com/w/cpp/container/unordered_map/unordered_map (1)
     */
    explicit HashTable(size_t bucket_count) {
        items_.resize(bucket_count);
    }

    HashTable(const HashTable& other) {
        size_ = other.size_;
        items_ = other.items_;
    }

    ~HashTable() {
        Clear();
    }

    /*
     * See https://en.cppreference.com/w/cpp/container/unordered_map/empty
     *
     * Returns true if the tree is empty, false otherwise
     */
    bool Empty() const {
        return size_ == 0;
    }

    /*
     * See https://en.cppreference.com/w/cpp/container/unordered_map/size
     *
     * Returns the number of elements in the container
     */
    size_t Size() const {
        return size_;
    }

    /*
     * See https://en.cppreference.com/w/cpp/container/unordered_map/clear
     *
     * Erases all elements from the container.
     */
    void Clear() {
        if (Empty()) {
            return;
        }
        size_t current_size = items_.size();
        size_ = 0;
        items_.clear();
        items_.resize(current_size);
    }

    /*
     * See https://en.cppreference.com/w/cpp/container/unordered_map/operator_at
     *
     * Returns a reference to the value that is mapped to a key equivalent to key.
     */
    T& operator[](const Key& key) {
        if (Find(key) == End()) {
            Insert(key, 0);
        }
        return items_[GetSlot(key)].value;
    }

    /*
     * See https://en.cppreference.com/w/cpp/container/unordered_map/insert
     *
     * Returns a bool value set to true if the insertion took place.
     */
    std::pair<Iterator, bool> Insert(const Key& key, const T& value) {
        if (ShouldRehash()) {
            PerformRehash();
        }
        Iterator it = Iterator(this, 0);
        if (Find(key) != End()) {
            return std::make_pair(it, false);
        }
        for (size_t i = 0; i < items_.size(); ++i) {
            size_t slot = ComputeIndex(key, i);
            Item item = items_[slot];
            if (item.state != HashState::Occupied) {
                items_[slot] = Item(key, value);
                size_++;
                it = Iterator(this, slot);
                return std::make_pair(it, true);
            }
        }
        return std::make_pair(it, false);
    }

    /*
     * See https://en.cppreference.com/w/cpp/container/unordered_map/erase
     *
     * Removes the element at position.
     * Returns iterator following the last removed element.
     */
    Iterator Erase(const Key& key) {
        if (Find(key) != End()) {
            for (size_t i = 0; i < items_.size(); ++i) {
                size_t slot = ComputeIndex(key, i);
                Item item = items_[slot];
                if (key_equal_(key, item.key)) {
                    items_[slot] = Item(HashState::Deleted);
                    size_--;
                    return Iterator(this, slot);
                }
            }
        }
        return End();
    }

    /*
     * See https://en.cppreference.com/w/cpp/container/unordered_map/find
     *
     * Finds an element with key.
     * Return iterator to an element with key. If no such element is found the
     * End() iterator is returned
     */
    Iterator Find(const Key& key) {
        for (size_t i = 0; i < items_.size(); ++i) {
            size_t slot = ComputeIndex(key, i);
            if (items_[slot].state == HashState::None) {
                // Item not found, no need to search further, exit early
                return End();
            } else {
                if (key_equal_(key, items_[slot].key)) {
                    return Iterator(this, slot);
                }
            }
        }
        return End();
    }

    Iterator Begin() {
        return Empty() ? End() : Iterator(this, 0);
    }

    Iterator End() {
        return Iterator(this, items_.size());
    }

    // Methods to support Range based for-loop

    Iterator begin() {  // NOLINT
        return Begin();
    }

    Iterator end() {  // NOLINT
        return End();
    }

private:
    struct Item {
        Key key;
        T value;
        std::pair<Key, T> pair;
        HashState state;

        explicit Item(HashState preferred_state = HashState::None) : key(), value() {
            state = preferred_state;
        }

        Item(Key new_key, T val) {
            key = new_key;
            value = val;
            state = HashState::Occupied;
            pair = std::make_pair(key, value);
        }
    };

    enum class HashState { None = 0, Deleted, Occupied };

private:
    static const size_t kInitialBucketSize = 10;
    static const size_t kBucketExpansionFactor = 2;
    const float load_factor_threshold_ = 0.5;

private:
    // Trail count should be < bucket_size
    size_t ComputeIndex(const Key& key, const size_t trail_count) const {
        return (hash_(key) + trail_count) % items_.size();
    }

    size_t GetSlot(const Key& key) {
        for (size_t i = 0; i < items_.size(); ++i) {
            size_t slot = ComputeIndex(key, i);
            Item item = items_[slot];
            if (key_equal_(key, item.key)) {
                return slot;
            }
        }
        return 0;
    }

    bool ShouldRehash() {
        float load_factor = (size_ / (float)items_.size());
        return (load_factor > load_factor_threshold_);
    }

    void PerformRehash() {
        HashTable<Key, T> new_table(items_.size() * kBucketExpansionFactor);
        for (size_t i = 0; i < items_.size(); ++i) {
            Item item = items_[i];
            if (item.state == HashState::Occupied) {
                new_table.Insert(item.key, item.value);
            }
        }
        std::swap(items_, new_table.items_);
        std::swap(size_, new_table.size_);
    }

private:
    size_t size_ = 0;
    std::vector<Item> items_;
    Hash hash_{};
    KeyEqual key_equal_{};
};

class Solver {
public:
    void ProcessInput() {
        int n;
        std::cin >> n;
        for (int i = 0; i < n; ++i) {
            std::string cmd;
            std::cin >> cmd;
            if (cmd == "Insert") {
                ProcessInsert();
            } else if (cmd == "Delete") {
                ProcessDelete();
            } else if (cmd == "Empty") {
                ProcessEmptyCommand();
            } else if (cmd == "Clear") {
                ClearHash();
            } else if (cmd == "Size") {
                PrintSize();
            } else if (cmd == "Find") {
                ProcessFind();
            } else if (cmd == "operator") {
                ProcessOperator();
            }
        }
    }

private:
    void ProcessInsert() {
        int key;
        int val;
        std::cin >> key >> val;
        std::cout << hash_.Insert(key, val).second << std::endl;
    }

    void ProcessFind() {
        int val;
        std::cin >> val;
        std::cout << (hash_.Find(val) != hash_.end()) << std::endl;
    }

    void ProcessDelete() {
        int key;
        std::cin >> key;
        std::cout << (hash_.Erase(key) != hash_.end()) << std::endl;
    }

    void ProcessEmptyCommand() {
        std::cout << hash_.Empty() << std::endl;
    }

    void PrintSize() {
        std::cout << hash_.Size() << std::endl;
    }

    void ClearHash() {
        hash_.Clear();
        std::cout << "Clear" << std::endl;
    }

    void ProcessOperator() {
        int key;
        int val;
        std::cin >> key >> val;
        if (hash_.Find(key) != hash_.end()) {
            std::cout << key << " " << hash_[key] << std::endl;
            hash_[key] = val;
        } else {
            hash_[key] = val;
            std::cout << key << " " << val << std::endl;
        }
    }

private:
    HashTable<int, int> hash_;
};

int main() {
    Solver solver;
    solver.ProcessInput();
    return 0;
}