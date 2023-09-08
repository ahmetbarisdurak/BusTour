#pragma once
#include "ObjectPool.h"

template <class T, unsigned int N>
class LinkedListIterator {
private:
	Node<T>* first;
	Node<T>* currentNode;
	template<typename U, unsigned int N>
	friend class LinkedList;


	template<typename U>
	friend class Node;

public:
	// For general iterator
	LinkedListIterator(Node<T>* head) : first(head) {
		currentNode = head;
	}

	// Checks if iterator has a next element or not
	bool HasNext() {
		return currentNode != NULL;
	}

	//Iterates through the next element and returns it
	T Next() {
		if (!HasNext())
			return {};

		T returnData = currentNode->data;
		currentNode = currentNode->next;

		return returnData;
	}

	// Checks if iterator has a previous element or not
	bool HasPrev() {
		if (currentNode == first)
			return false;
		return true;
	}

	//Iterates through the previous element and returns it
	T Prev() {
		if (!HasPrev())
			return {};

		Node<T>* temp = first;

		while (temp->next != currentNode) {
			temp = temp->next;
		}

		T returnData = temp->data;
		currentNode = temp;

		return returnData;
	}

};