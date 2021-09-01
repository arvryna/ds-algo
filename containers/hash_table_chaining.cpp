#include <functional>
#include <iostream>
#include <vector>

template <typename Key, typename T, typename Hash = std::hash<Key>,
          typename KeyEqual = std::equal_to<Key>>

class HashTable {

private:
    struct Item {
        Key key;
        T value;
        Item* next;

        Item() {
            next = nullptr;
        }
    };

public:
    /*
     * See https://en.cppreference.com/w/cpp/named_req/ForwardIterator.
     */
    class Iterator : public std::iterator<std::forward_iterator_tag, std::pair<Key, T>> {

    public:
        Iterator(HashTable* table, size_t id, Item* item, bool set_begin = false) {
            current_item_ = item;
            bucket_size_ = table->buckets_.size();
            total_items_ = table->Size();
            bucket_id_ = id;
            table_ = table;
            if (set_begin) {
                bucket_id_ = 0;
                current_item_ = table->buckets_[bucket_id_];
                if (current_item_ == nullptr) {
                    for (bucket_id_ = 0; bucket_id_ < bucket_size_; bucket_id_++) {
                        current_item_ = table->buckets_[bucket_id_];
                        if (current_item_ != nullptr) {
                            break;
                        }
                    }
                }
            }
        }

        bool operator==(const Iterator& rhs) const {
            return table_ == rhs.table_ && bucket_id_ == bucket_size_;
        }

        bool operator!=(const Iterator& rhs) const {
            return !(*this == rhs);
        }

        Iterator& operator++() {
            current_item_ = current_item_->next;
            if (current_item_ == nullptr) {
                for (bucket_id_ = bucket_id_ + 1; bucket_id_ < bucket_size_; bucket_id_++) {
                    current_item_ = table_->buckets_[bucket_id_];
                    if (current_item_ != nullptr) {
                        break;
                    }
                }
                if (current_item_ == nullptr) {
                    bucket_id_ = bucket_size_;
                }
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator copy(*this);
            operator++();
            return copy;
        }

        std::pair<Key, T>& operator*() {
            pair_ = std::make_pair(current_item_->key, current_item_->value);
            return pair_;
        }

        std::pair<Key, T>* operator->() {
            pair_ = std::make_pair(current_item_->key, current_item_->value);
            return &pair_;
        };

    private:
        size_t total_items_;
        size_t bucket_size_;
        Item* current_item_;
        size_t bucket_id_;
        HashTable* table_;
        std::pair<Key, T> pair_;
    };

    /*
     * See https://en.cppreference.com/w/cpp/container/unordered_map/unordered_map (1)
     *
     * Constructs new container. The number of buckets to create is implementation-defined.
     */
    HashTable() {
        buckets_.resize(kInitialBucketSize);
    }

    /*
     * See https://en.cppreference.com/w/cpp/container/unordered_map/unordered_map (1)
     *
     * Constructs new container, uses bucket_count parameter as a minimal number of buckets to
     * create.
     */
    explicit HashTable(size_t bucket_count) {
        buckets_.resize(bucket_count);
    }

    HashTable(const HashTable& other) {
        buckets_.resize(other.size_);
        for (auto i : other) {
            Insert(i->key, i->value);
        }
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

        for (size_t i = 0; i < buckets_.size(); i++) {
            Item* node = buckets_[i];
            while (node != nullptr) {
                Item* temp = node;
                node = node->next;
                delete temp;
            }
            buckets_[i] = nullptr;
        }
        size_ = 0;
    }

    /*
     * See https://en.cppreference.com/w/cpp/container/unordered_map/operator_at
     *
     * Returns a reference to the value that is mapped to a key equivalent to key.
     */
    T& operator[](const Key& key) {
        Item* item = std::get<1>(GetItem(key));
        if (item == nullptr) {
            Insert(key, 0);
            return (std::get<1>(GetItem(key)))->value;
        }
        return item->value;
    }

    /*
     * See https://en.cppreference.com/w/cpp/container/unordered_map/insert
     *
     * Returns a bool value set to true if the insertion took place.
     */
    std::pair<Iterator, bool> Insert(const Key& key, const T& value) {
        Iterator it = Iterator(this, 0, nullptr);
        if (Find(key) != End()) {
            return std::make_pair(it, false);
        }

        size_t index = GenerateHash(key);
        Item* new_item = new Item();
        new_item->key = key;
        new_item->value = value;

        Item* node = buckets_[index];

        if (node == nullptr) {
            buckets_[index] = new_item;
        } else {
            while (node->next != nullptr) {
                node = node->next;
            }
            node->next = new_item;
        }

        size_++;
        it = Iterator(this, index, new_item);
        return std::make_pair(it, true);
    }

    /*
     * See https://en.cppreference.com/w/cpp/container/unordered_map/erase
     *
     * Removes the element at position.
     * Returns iterator following the last removed element.
     */
    Iterator Erase(const Key& key) {
        // clang-format off
        auto [prev, current_node, bucket_it] = GetItem(key);
        // clang-format on
        Item* node_to_delete = nullptr;
        node_to_delete = current_node;
        size_t index = 0;
        if (prev == nullptr && current_node != nullptr) {
            index = GenerateHash(key);
            buckets_[index] = current_node->next;
        } else if (prev != nullptr && current_node != nullptr) {
            prev->next = current_node->next;
        } else {
            return End();
        }

        delete node_to_delete;
        size_--;
        return Iterator(this, index, nullptr);
    }

    /*
     * See https://en.cppreference.com/w/cpp/container/unordered_map/find
     *
     * Finds an element with key.
     * Return iterator to an element with key. If no such element is found the
     * End() iterator is returned
     */
    Iterator Find(const Key& key) {
        auto tuples = GetItem(key);
        Item* item = std::get<1>(tuples);
        if (item == nullptr) {
            return End();
        } else {
            return Iterator(this, std::get<2>(tuples), item);
        }
    }

    Iterator Begin() {
        // Go to the first element in the bucket
        if (Empty()) {
            return End();
        } else {
            return Iterator(this, 0, buckets_[0], true);
        }
    }

    /*
     * See https://en.cppreference.com/w/cpp/container/unordered_map/end
     *
     * Returns an iterator to the element following the last element
     */
    Iterator End() {
        return Iterator(this, buckets_.size(), nullptr);
    }

    // Methods to support Range based for loop for the container

    Iterator begin() {  // NOLINT
        return Begin();
    }

    Iterator end() {  // NOLINT
        return End();
    }

private:
    static const size_t kInitialBucketSize = 100;

    size_t size_ = 0;

    std::vector<Item*> buckets_;

    size_t GenerateHash(const Key& key) const {
        size_t res = 0;
        size_t hash = Hash{}(key);
        res = hash % buckets_.size();
        return res;
    }

    // Returns previous and current item for a given key
    std::tuple<Item*, Item*, size_t> GetItem(const Key& key) const {
        size_t bucket_id = GenerateHash(key);
        Item* node = buckets_[bucket_id];
        Item* prev = nullptr;
        while (node != nullptr) {
            if (KeyEqual{}(node->key, key)) {
                return std::make_tuple(prev, node, bucket_id);
            }
            prev = node;
            node = node->next;
        }
        return std::make_tuple(nullptr, nullptr, 0);
    }
};

void ProcessUserInputs() {
    int n;
    std::cin >> n;
    HashTable<int, int> hash(n);
    for (int i = 0; i < n; i++) {
        std::string cmd;
        std::cin >> cmd;
        if (cmd == "Insert") {
            int key;
            int val;
            std::cin >> key >> val;
            std::cout << hash.Insert(key, val).second << std::endl;
        } else if (cmd == "Delete") {
            int key;
            std::cin >> key;
            std::cout << (hash.Erase(key) != hash.end()) << std::endl;
        } else if (cmd == "Empty") {
            std::cout << hash.Empty() << std::endl;
        } else if (cmd == "Clear") {
            hash.Clear();
            std::cout << "Clear" << std::endl;
        } else if (cmd == "Size") {
            std::cout << hash.Size() << std::endl;
        } else if (cmd == "Find") {
            int val;
            std::cin >> val;
            std::cout << (hash.Find(val) != hash.end()) << std::endl;
        } else if (cmd == "operator") {
            int key;
            int val;
            std::cin >> key >> val;
            if (hash.Find(key) != hash.end()) {
                std::cout << key << " " << hash[key] << std::endl;
                hash[key] = val;
            } else {
                hash[key] = val;
                std::cout << key << " " << val << std::endl;
            }
        }
    }
}

int main() {
    ProcessUserInputs();
    return 0;
}