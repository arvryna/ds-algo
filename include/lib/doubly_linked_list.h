#include <iostream>

template <typename T>
class DoublyLinkedList {
private:
    struct Node;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void Insert(T val);
    void Delete(Node *node);
    size_t Size();
    T Peek();

private:
    struct Node {
        T val;
        Node *next;
        Node *prev;
    };
    Node *head_;
    Node *tail_;
};