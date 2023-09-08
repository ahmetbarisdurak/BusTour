#pragma once

#include <iostream>

#define AVAILABLE 1
#define OCCUPIED 0

template<class T, unsigned int N>
class LinkedList;

template <class T>
class Node {
private:
	T data;
	Node<T>* next;
	template<typename U, unsigned int N>
	friend class LinkedList;

	template<typename U, unsigned int N>
	friend class LinkedListIterator;


public:
	Node(); // Constructor of Node
	Node(const T data);
};


template <class T, unsigned int N>
class ObjectPool {
private:
	T pool[N];
	int poolAvailability[N];
	int usedObjects;

public:
	ObjectPool();
	~ObjectPool();
	T* Allocate();
	bool Free(T* node);

};


template <class T, unsigned int N>
ObjectPool<T, N>::ObjectPool() : usedObjects(0) { 
	for (int i = 0; i < N; i++) {
		poolAvailability[i] = AVAILABLE;
	}
}


template <class T, unsigned int N>
ObjectPool<T, N>::~ObjectPool() {

}


template <class T, unsigned int N>
typename T* ObjectPool<T, N>::Allocate() {
	
	for (int i = 0; i < N; i++) {
		if (poolAvailability[i] == AVAILABLE)
		{
			usedObjects++;
			poolAvailability[i] = OCCUPIED;
			return &pool[i];
		}
	}
	
	//cout << "There is no capacity for object" << endl;
	return NULL;
}

template <class T, unsigned int N>
bool ObjectPool<T, N>::Free(T* freedObject) {

	for (int i = 0; i < N; i++) {
		if (freedObject == &pool[i]) {
			poolAvailability[i] = AVAILABLE;
			//pool[i] = T(); // Reset the values inside object
			usedObjects--;

			//cout << "Free is completed returning the value " << endl;
			return true;
		}
	}
	
	//cout << "This object is not in the pool" << endl;
	return false;
}