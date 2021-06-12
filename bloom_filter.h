
#ifndef bloom_filter_h
#define bloom_filter_h

template <typename Key, typename Value>
class BloomFilter {
public:
    BloomFilter(size_t n);
	Value &operator[](Key key);
	bool Delete(Key key);
	bool Empty();
    void Clear();
	Value Peek(); // Returns the head of the cache
    size_t Size();

private:
    size_t size_;
};

#endif /* bloom_filter_h */