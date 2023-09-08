#pragma once

#include<iostream>
#include <LinkedListIterator.h>
#include <ObjectPool.h>

template <class T, unsigned int N>
class LinkedList {
protected:
	Node<T>* first;
	Node<T>* last;
	int size;

	template<typename U, unsigned int N>
	friend class LinkedListIterator;
	ObjectPool<Node<T>, N> nodePool;
	
public:
	LinkedList();
	~LinkedList();  // Destructor to release memory
	void Clear();
	bool PushBack(const T& element);
	bool PopBack();
	T Front();
	T Back();
	int GetSize();

	bool Insert(LinkedListIterator<T, N> pos, const T& element);
	bool Erase(LinkedListIterator<T, N>& pos);
	LinkedListIterator<T, N> GetIterator();

	// Operator Overloading
	LinkedList<T, N>& operator=(LinkedList<T, N>& other);

	template <class T, unsigned int N>
	friend std::ostream& operator<< (std::ostream& os, LinkedList<T, N>& list);

	
};

template <class T, unsigned N>
std::ostream& operator<< (std::ostream& os, LinkedList<T, N>& list) {
	if (list.first == NULL)
		return os;

	LinkedListIterator<T, N> temp = list.GetIterator();

	while (temp.HasNext()) {
		std::cout << temp.Next() << "->";
	}

	return os;
}

template <class T>
Node<T>::Node() {
	this->next = NULL;
}

template <class T>
Node<T>::Node(const T data) {
	this->next = NULL;
	this->data = data;
}

template <class T, unsigned int N>
LinkedList<T, N>::LinkedList() {
	size = 0;
	first = NULL;
	last = NULL;
}

template <class T, unsigned int N>
LinkedList<T, N>::~LinkedList() {
	Clear();
}

template <class T, unsigned int N>
int LinkedList<T, N>::GetSize() {
	return size;
}

template <class T, unsigned int N>
void LinkedList<T, N>::Clear() {

	if (first == nullptr)
		return;
	
	Node<T>* temp = first;

	while (temp->next != NULL) {
		Node<T>* next = temp->next;
		nodePool.Free(temp);
		temp = next;
	}

	first = NULL;
	last = NULL;
	size = 0;
}

template <class T, unsigned int N>
bool LinkedList<T, N>::PushBack(const T& element) {
	if (first == NULL) {

		Node<T>* allocatedNode = nodePool.Allocate();
	
		if (allocatedNode == NULL)
			return false;

		allocatedNode->data = element;
		allocatedNode->next = NULL;

		first = allocatedNode;

		last = first;
		//cout << "Element pushed to first place!" << endl;

	}
	else {

		Node<T>* allocatedNode = nodePool.Allocate();

		if (allocatedNode == NULL)
			return false;

		allocatedNode->data = element;
		allocatedNode->next = NULL;

		last->next = allocatedNode;
		//cout << "Element pushed to back of the list " << endl;
		last = last->next;
	}

	size++;
	return true;
}

template <class T, unsigned int N>
bool LinkedList<T, N>::PopBack() {

	if (first == NULL) {
		//cout << "Linked list is empty!" << endl;
		return false;
	}

	if (first->next == NULL) {
		nodePool.Free(first);
		first = NULL;
		last = NULL;
	}

	Node<T>* temp = first;

	while (temp != NULL) {
		if (temp->next->next == NULL) {
			nodePool.Free(temp->next);
			nodePool.Free(new Node<T>()); // Outside object for testing
			temp->next = NULL;
			last = temp;
			//cout << "last item is popped" << endl;
			break;
		}
		temp = temp->next;
	}

	size--;
	return true;
}

template <class T, unsigned int N >
T LinkedList<T, N>::Front() {

	if (first == NULL)
		return NULL;

	return first->data;
}

template <class T, unsigned int N>
T LinkedList<T, N>::Back() {
	if (last == NULL)
		return NULL;

	return last->data;
}

template <class T, unsigned int N>
LinkedListIterator<T, N> LinkedList<T, N>::GetIterator()
{
	return LinkedListIterator<T, N>(first);
}

template <class T, unsigned int N>
bool LinkedList<T, N>::Insert(LinkedListIterator<T, N> pos, const T& element) {

	if (first == pos.currentNode) {
		Node<T>* allocatedNode = nodePool.Allocate();

		if (allocatedNode == NULL)
			return false;

		allocatedNode->data = element;
		allocatedNode->next = NULL;

		first = allocatedNode;
		first->next = pos.currentNode;
		
	}
	else if (last->next == pos.currentNode) {
		PushBack(element);
	}
	else {
		Node<T>* temp = pos.currentNode;
		pos.Prev();

		Node<T>* allocatedNode = nodePool.Allocate();

		if (allocatedNode == NULL)
			return false;

		allocatedNode->data = element;
		allocatedNode->next = NULL;

		pos.currentNode->next = allocatedNode;
		pos.currentNode->next->next = temp;
	}

	size++;
	return true;
}

template <class T, unsigned int N>
bool LinkedList<T, N>::Erase(LinkedListIterator<T, N>& pos) {

	if (pos.currentNode == NULL) {
		//cout << "Can't delete the null node" << endl;
		return false;
	}
	else if (first == pos.currentNode) { // If iterator is at the first element
		Node<T>* temp = first;
		first = first->next;
		nodePool.Free(temp);
		pos.Next();
		
	}
	else if (last == pos.currentNode) { // If iterator is at the end element

		pos.Prev();
		last = pos.currentNode;
		nodePool.Free(last->next);
			//cout << "Free is successful1" << endl;
	}
	else {
		Node<T>* nextNode = pos.currentNode->next;
		pos.Prev();
		
		nodePool.Free(pos.currentNode->next);
			//cout << "Free is successful2" << endl;

		pos.currentNode->next = nextNode;

	}
	//cout << "Erase is succesful3" << endl;
	size--;
	return true;
}

// Assignment operator
template <class T, unsigned int N>
LinkedList<T, N>& LinkedList<T, N>::operator=(LinkedList<T, N>& other) {
	if (this == &other) {
		return *this; // Self-assignment check
	}

	// Clear the current list
	Clear();

	LinkedListIterator<T, N> otherIterator = other.GetIterator();

	while (otherIterator.HasNext()) {
		PushBack(otherIterator.Next());
	}

	return *this;
}
