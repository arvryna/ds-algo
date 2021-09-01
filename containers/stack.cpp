#include <iostream>
// Copyright 2021 <arv>
// Codereview - 3rd attempt

/*
2) I see that you have moved the if condition to the loop. Better then just handle
the empty stack case separately.
5) I suggest making a simple constructor for Node: Node(Node* next, int data).

- Cleaned main function()
- Removed the unwanted function CopyStackHelper
- Pop() method, removed unnessary check as there is a guarentee
that it won't be called for empty function
*/

class Stack {
public:
    Stack() {
        head_ = nullptr;
        size_ = 0;
    }

    // Copies data from "other" stack into "this" stack (on initialization)
    Stack(const Stack& other) {
        Node* cur_node = other.head_;
        Node* prev = nullptr;
        while (cur_node != nullptr) {
            Node* new_node = new Node;
            new_node->data = cur_node->data;
            new_node->next = nullptr;
            if (prev != nullptr) {
                prev->next = new_node;
            } else {
                head_ = new_node;
            }
            prev = new_node;
            cur_node = cur_node->next;
            size_++;
        }
    }

    // Copy data from "other" stack into "this" stack (on assignment)
    Stack& operator=(Stack other) {
        std::swap(size_, other.size_);
        std::swap(head_, other.head_);
        return *this;
    }

    ~Stack() {
        Clear();
    }

    int Top() {
        return head_->data;
    }

    bool Empty() const {
        return (size_ == 0);
    }

    size_t Size() const {
        return size_;
    }

    void Push(int value) {
        Node* new_head = new Node;
        new_head->data = value;
        new_head->next = head_;
        head_ = new_head;
        size_++;
    }

    void Pop() {
        Node* prev_head = head_;
        head_ = prev_head->next;
        delete prev_head;
        size_--;
    }

    void Clear() {
        while (head_ != nullptr) {
            Pop();
        }
        size_ = 0;
    }

private:
    struct Node {
        int data;
        Node* next;
    };
    int size_ = 0;
    Node* head_ = nullptr;
};

void StackInterfaceTester(){
    int n;
    std::cin >> n;
    Stack s;
    for (int i = 0; i < n; i++) {
        std::string cmd;
        std::cin >> cmd;
        if (cmd == "Push") {
            int val = 0;
            std::cin >> val;
            s.Push(val);
            std::cout << val << std::endl;
        } else if (cmd == "Pop") {
            std::cout << s.Top() << std::endl;
            s.Pop();
        } else if (cmd == "Size") {
            std::cout << s.Size() << std::endl;
        } else if (cmd == "Clear") {
            s.Clear();
            std::cout << "Clear" << std::endl;
        } else if (cmd == "Top") {
            std::cout << s.Top() << std::endl;
        }
    }
}

int main() {
    StackInterfaceTester();
    return 0;
}

