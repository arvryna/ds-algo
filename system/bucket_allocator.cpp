#include <iostream>
#include <vector>

template <typename T>

// Bucket allocator compatible with std::allocator_traits => allocate, deallocate and typedef
class bucket_allocator {
public:
    // Type of the value, this allocator is being allocated with.
    typedef T value_type;

    explicit bucket_allocator(const size_t size = kMaxThresholdSize) {
        threshold_size_ = size;
    }

    /* Allocate chunk with size n */

    T* allocate(const size_t n) {
        T* address = nullptr;
        if (n > threshold_size_) {
            address = create_bucket(n, n);
            return address;
        }

        // check for freespace in existing buckets
        size_t bucket_size = buckets_.size();
        for (size_t i = 0; i < bucket_size; ++i) {
            bucket current_bucket = buckets_[i];
            if (current_bucket.can_allocate(n)) {
                address = current_bucket.allocate(n);
                buckets_[i] = current_bucket;
                return address;
            }
        }

        // create new bucket
        address = create_bucket(threshold_size_, n);
        return address;
    }

    /* Deallocate chunk with its pointer and size */

    void deallocate(T* ptr, const size_t n) {
        for (size_t i = 0; i < buckets_.size(); i++) {
            bucket current_bucket = buckets_[i];
            if (current_bucket.is_chunk_present(ptr)) {
                current_bucket.deallocate(n);
                buckets_[i] = current_bucket;
                if (current_bucket.should_delete_bucket(n)) {
                    delete[] reinterpret_cast<char*>(current_bucket.base_address);
                    buckets_.erase(buckets_.begin() + i);
                    break;
                }
            }
        }
    }

    // Deleting implicitly
    bucket_allocator(const bucket_allocator&) = delete;
    bucket_allocator& operator=(const bucket_allocator&) = delete;

    // Desctructor is not necessary
    ~bucket_allocator() = default;

private:
    T* create_bucket(size_t threshold, size_t n) {
        bucket new_bucket(threshold);
        T* chunk_address = new_bucket.allocate(n);
        buckets_.push_back(new_bucket);
        return chunk_address;
    }

private:
    struct bucket {
        T* base_address = nullptr;
        size_t max_size;
        size_t allocation_count;
        size_t deallocation_count;

        explicit bucket(size_t threshold) {
            max_size = threshold;
            allocation_count = 0;
            deallocation_count = 0;
            /*Allocating array of chars(as its size is guaranteed to be 1 byte) new char[n], this
             * simply allocates n bytes of data, so in our case her we allocate size of T * number
             * of such elements as a array reinterpret_cast changes the char type of pointer(char *)
             * to T type of pointer (T*)*/
            base_address = reinterpret_cast<T*>(new char[sizeof(T) * threshold]);
        }

        T* allocate(size_t n) {
            T* address = get_address_to_free_chunk();
            allocation_count += n;
            return address;
        }

        void deallocate(size_t n) {
            deallocation_count += n;
        }

        // Check if the chunk part of this bucket
        bool is_chunk_present(T* address) {
            return (address >= base_address && address <= base_address + allocation_count);
        }

        // Returns true if all chunks in the bucket are deallocated.
        bool should_delete_bucket(size_t n) {
            return (allocation_count == deallocation_count);
        }

        bool can_allocate(size_t expected_size) {
            return allocation_count + expected_size <= max_size;
        }

        // Get address of the next free available chunk
        T* get_address_to_free_chunk() {
            return (base_address + allocation_count);
        }
    };

private:

    static const size_t kMaxThresholdSize = 1024;
    size_t threshold_size_;
    std::vector<bucket> buckets_;
};

/* --- Driver code --- */

struct Logger {
    Logger() {
        std::cout << "Constructed at" << this << std::endl;
    }

    ~Logger() {
        std::cout << "Destructed at" << this << std::endl;
    }
};

int main() {
    bucket_allocator<Logger> alloc;
    Logger* chunk = alloc.allocate(100);
    Logger* chunk2 = alloc.allocate(200);
    alloc.deallocate(chunk, 100);
    alloc.deallocate(chunk2, 200);
    return 0;
}