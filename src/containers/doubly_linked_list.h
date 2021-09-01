#include <iostream>

template <typename T>
class DoublyLinkedList {
public:
    struct Node;
    DoublyLinkedList();

    ~DoublyLinkedList();

    // Insert element at the Head - O(n)
    void Insert(T val);

    // Search and delete node with value - O(n)
    void Erase(T val);

    // Erasing the node directly - O(1)
	void Erase(Node *node);
    
    size_t Size();
    
    bool Empty();

    // Get value of the head 
    T Peek();
    
    void Clear();

    struct Node {
        T val;
        Node *next;
        Node *prev;
        Node() {
            next = nullptr;
            prev = nullptr;
        }
    };

private:
    Node *head_ = nullptr;
    Node *tail_ = nullptr;
    size_t size_ = 0;
};