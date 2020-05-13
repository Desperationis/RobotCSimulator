#pragma once
#include <Debug/Log.h>
#include <array>
#include "tsl/hopscotch_map.h"
#include <iostream>


/*
	To be inhereted by a packed_array to create a generic class with a virtual interface.
*/
class Ipacked_array {
public:
	Ipacked_array() = default;
	virtual void erase(size_t index) = 0;
};

/*
	A packed array of anything.
*/
template <class T, size_t SIZE>
class packed_array : public Ipacked_array {
public:
	void insert(size_t key, T data) {
		// won't do anything if entity already exists
		if (keyToIndex.find(key) == keyToIndex.end()) {
			// insert data at the end of the array
			size_t newIndex = size;
			components[newIndex] = data;

			// update maps to point to the new index
			keyToIndex[key] = newIndex;
			indexToKey[newIndex] = key;
		
			// increment size of valid entries
			size++;
		}
	}

	void erase(size_t key) override {
		// won't do anything if entity doesn't exist
		if (keyToIndex.find(key) != keyToIndex.end()) {
			size_t deletedIndex = keyToIndex[key];
			size_t lastIndex = size - 1;
			size_t lastKey = indexToKey[lastIndex];

			// copy data from the back of the array to the deleted entity's index
			components[deletedIndex] = components[lastIndex];

			// copy map data from the back of the array to the deleted entity's lookup
			keyToIndex[lastKey] = deletedIndex; // back entity will point to new index
			indexToKey[deletedIndex] = lastKey;

			// erase the residue
			keyToIndex.erase(key);
			indexToKey.erase(lastIndex);

			size--;
		}
	}

	T& get(size_t key) {
		return components[keyToIndex[key]];
	}


private:
	// a generic array of components
	std::array<T, SIZE> components;

	tsl::hopscotch_map<size_t, size_t> keyToIndex;

	tsl::hopscotch_map<size_t, size_t> indexToKey;

	// the number of spots in the array that are in use
	size_t size;
};