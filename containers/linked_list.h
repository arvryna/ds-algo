template <typename T>
class DoublyLinkedList {
private:
    struct Node;

public:
    void Insert(T val);
    void Delete(Node *node);
    size_t Size();

private:
    struct Node {
        T val;
        Node *next;
        Node *prev;
    };
    Node *head_;
    Node *tail_;
};