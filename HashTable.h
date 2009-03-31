/******************************
 * Author: Adam Coffman
 *
 * Filename: HashTable.h
 *
 * Description: This is the header file for the Hash Table
 * It contains variables and function protoypes. This table
 * uses double hashing for collision resolution, and lazy deletion.
 * Values are actually removed on Rehashing. 
 * 
 * Build Instructions: A makefile is included in the project directory
 * 	program can be run as ./driver
 *
 ******************************/
#ifndef HASH_H
#define HASH_H

using namespace std;

#include "SearchableADT.h"
#include <string>
#include <cmath>

template <typename T>
class HashTable : public SearchableADT<T>{
	public:
		HashTable();
		HashTable(int initialSize);
		~HashTable();
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
		int initSize;

		double lambda(){return (double)numElements/tableSize;};

		int h1(T elem);
		int h2(T elem);
		int search(T elem);
		void rehash();
		void insertIntoTable(T value, HashNode* &table);
};


#include "HashTable.cpp"

#endif
