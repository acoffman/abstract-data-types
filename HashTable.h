/******************************
 * Author: Adam Coffman
 *
 * Filename: HashTable.h
 *
 * Description: This is the header file for the Hash Table
 * It contains variables and function protoypes. This table
 * uses double hashing for collision resolution
 * 
 * Build Instructions: A makefile is included in the project directory
 * 	program can be run as ./driver
 *
 ******************************/
#ifndef HASH_H
#define HASH_H

using namespace std;

#include "SearchableADT.h"

template <typename T>
class HashTable : public SearchableADT<T>{
	public:
		int loadFromFile(string filename);
		void clear();
		void insertEntry(T value);
		void deleteEntry(T value);
		bool isThere(T value);
		int numEntries();
		int treeHeight(){return -1;};
		int tableCapacity(); 

	private:
			struct HashNode{
			T elem;
			bool deleted;
		};
		
		HashNode *table;
		int tableSize;
		int numElements;

		bool is_empty(int index);
		int h1(T elem);
		int h2(T elem);
};


#include "HashTable.cpp"

#endif
