#include "lib/doubly_linked_list.h"

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
	size_ = 0;
	head_ = nullptr;
	tail_ = nullptr;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	Clear();
}

template <typename T>
void DoublyLinkedList<T>::Insert(T val) {
	size_++;
}

template <typename T>
bool DoublyLinkedList<T>::Empty() {
	return (size_ == 0);
}

template <typename T>
void DoublyLinkedList<T>::Clear() {
	if(Empty()){
		return;
	}
	// Node *node = head_;
	// while(node->next != nullptr){
	// 	Node *temp = node;
	// 	node = node->next;
	// 	delete temp;
	// }
}

template <typename T>
void DoublyLinkedList<T>::Erase(Node *node) {
	// Fix bugs here
    if (node != nullptr) {
        if (head_ == node) {
            head_ = node->next;
        } else if (tail_ == node) {
            tail_ = node->prev;
        } else {
            node->prev = node->next;
        }
		delete node;
		size_--;
    }
}

template <typename T>
T DoublyLinkedList<T>::Peek() {
    return head_->val;
}
