#pragma once

template <class T, unsigned int N>
class StaticVectorIterator {
private:
	int currentIndex = 0;
	int vectorSize;
	T* vectorData;
	template<typename U, unsigned int N>
	friend class StaticVector;

public:
	// For general iterator
	StaticVectorIterator(int size, T* staticVectorData) : vectorSize(size), vectorData(staticVectorData) {
	}

	//  For specific iterator with given index
	StaticVectorIterator(int index, int size, T* staticVectorData) :
		currentIndex(index), vectorSize(size), vectorData(staticVectorData) {
	}

	// Checks if iterator has a next element or not
	bool HasNext() {
		if (currentIndex < vectorSize)
			return true;

		return false;
	}

	//Iterates through the next element and returns it
	T Next() {
		if (!HasNext())
			return {};

		return vectorData[currentIndex++];
	}

	// Checks if iterator has a previous element or not
	bool HasPrev() {
		if (currentIndex > 0)
			return true;

		return false;
	}

	//Iterates through the previous element and returns it
	T Prev() {
		if (!HasPrev())
			return {};

		return vectorData[--currentIndex];
	}

};