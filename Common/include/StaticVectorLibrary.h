#pragma once

#include<iostream>
#include <ostream>
#include "StaticVectorIterator.h"


template <class T, unsigned int N>
class StaticVector {
public:
	StaticVector();

	StaticVector(T element);

	~StaticVector() = default;

	// adding a new element at the end of the vector
	bool PushBack(T element);

	// Removes the last element in the vector
	bool PopBack();

	// returns the first element of the vector
	T First();

	// returns the last element of the vector
	T Last();

	// returns the size of the vector
	const int GetSize();

	T& GetIndex(int index);
	
	void SetIndex(int index, T element);

	// Starts iterator index from the beginning of the vector
	StaticVectorIterator<T, N> Begin();

	// Starts iterator index from the ending of the vector
	StaticVectorIterator<T, N> End();

	// Starts iterator with first index as general
	StaticVectorIterator<T, N> GetIterator();

	void Sort(bool (*comparisonFunction)(const T&, const T&));


	// Operator Overloading
	StaticVector& operator=(const StaticVector& other);
	T& operator[](int index);

	template <class T, unsigned int N>
	friend std::ostream& operator<<(std::ostream& os, StaticVector<T, N>& list);

private:
	const int capacity = N;
	int size;
	T staticVectorData[N];
};


template <class T, unsigned int N>
std::ostream& operator<<(std::ostream& os, StaticVector<T, N>& list) {

	for (int i = 0; i < list.GetSize(); i++)
		os << list.staticVectorData[i] << " ";

	os << std::endl;
	return os;
}

template <class T, unsigned int N>
T& StaticVector<T, N>::operator[](int index) {
	return staticVectorData[index];
}

template <class T, unsigned int N>
StaticVector<T, N>::StaticVector() : size(0) {
}

template <class T, unsigned int N>
StaticVector<T, N>::StaticVector(T element) {
	size = N;
	for (int i = 0; i < N; i++) {
		staticVectorData[i] = element;
	}
}

template <class T, unsigned int N>
bool StaticVector<T, N>::PushBack(T element) {
	if (size >= capacity) {
		std::cout << "Out of capacity" << std::endl;
		return false;
	}
	else {
		staticVectorData[size++] = element;
		return true;
	}
}

template <class T, unsigned int N>
T& StaticVector<T, N>::GetIndex(int index) {
	return staticVectorData[index];
}

template <class T, unsigned int N>
void StaticVector<T, N>::SetIndex(int index, T element) {
	staticVectorData[index] = element;

}

template <class T, unsigned int N>
bool StaticVector<T, N>::PopBack() {
	if (size == 0)
		return false;
	else {
		size--;
		return true;
	}
}

template <class T, unsigned int N>
const int StaticVector<T, N>::GetSize() {
	return size;
}

template <class T, unsigned int N>
T StaticVector<T, N>::First() {
	return staticVectorData[0];
}

template <class T, unsigned int N>
T StaticVector<T, N>::Last() {
	return staticVectorData[size - 1];
}

template <class T, unsigned int N>
StaticVectorIterator<T, N> StaticVector<T, N>::Begin() {
	return StaticVectorIterator<T, N>(0, size, staticVectorData);
}

template <class T, unsigned int N>
StaticVectorIterator<T, N> StaticVector<T, N>::End() {
	return StaticVectorIterator<T,N>(size, size, staticVectorData);
}

template <class T, unsigned int N>
StaticVectorIterator<T, N> StaticVector<T, N>::GetIterator()
{
	return StaticVectorIterator<T,N>(size, staticVectorData);
}

template <class T>
bool operator<(const T& lhs, const T& rhs) {
	if (lhs < rhs)
		return true;
	return false;
}

template <class T , unsigned int N>
void StaticVector<T, N>::Sort(bool (*comparisonFunction)(const T&, const T&)) {

	int i, j;
	T key;
	for (i = 1; i < N; i++) {
		key = staticVectorData[i];
		j = i - 1;

		while (j >= 0 && comparisonFunction(staticVectorData[j], key) ) {
			staticVectorData[j + 1] = staticVectorData[j];
			j = j - 1;
		}
		staticVectorData[j + 1] = key;
	}

}

template <class T, unsigned int N>
StaticVector<T, N>& StaticVector<T, N>::operator=(const StaticVector& other) {
	if (this != &other) {
		size = other.size;
		for (int i = 0; i < size; ++i) {
			staticVectorData[i] = other.staticVectorData[i];
		}
	}
	return *this;
}
