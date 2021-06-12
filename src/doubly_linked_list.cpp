#include "lib/doubly_linked_list.h"

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(){
	std::cout << "Allocating DLL";
	
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList(){
}

template<typename T>
void DoublyLinkedList<T>::Insert(T val){
	std::cout << "Inserting new element in DLL";
}

