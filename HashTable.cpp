#include <iostream>

//CONSTRUCTORS AND DESTRUCTOR
template <class T>
HashTable<T>::HashTable(){
	tableSize = initSize = 101;
	table = new HashNode[tableSize];
	numElements = 0;
}

template <class T>
HashTable<T>::HashTable(int initialSize){
	tableSize = initSize = initialSize;
	table = new HashNode[tableSize];
	numElements = 0;
}

template <class T>
HashTable<T>::~HashTable(){
	delete [] table;
}
//END CONSTRUCTORS AND DESCTRUCTOR


//CLEAR AND LOAD//
template <class T>
void HashTable<T>::clear(){
	numElements = 0;
	tableSize = initSize;
	delete [] table;
	table = new HashNode[initSize];
}

template <class T>
int HashTable<T>::loadFromFile(string filename){
	ifstream fin;
	fin.open(filename.c_str());
	if(fin.fail()){
		return -1;
	}else{
		while(!fin.eof()){
			T word;
			fin >> word;
			insertEntry(word);
		}
	}
	return 0;
}
//END CLEAR AND LOAD

//TABLE STATS//
template <class T>
int HashTable<T>::tableCapacity(){ return tableSize;}

template <class T>
int HashTable<T>::numEntries(){ return numElements;}
//END TABLE STATS


//SEARCH, INSERT, AND DELETE//
template <class T>
bool HashTable<T>::isThere(T elem){return search(elem) != -1;}

template <class T>
void HashTable<T>::insertEntry(T value){
	insertIntoTable(value, table);
}

template <class T>
void HashTable<T>::deleteEntry(T value){
	int index = search(value);
	if(index != -1){
		table[index].deleted = true;
		--numElements;
	}
}

template <class T>
int HashTable<T>::search(T value){
	int hash_one = h1(value);
	int hash_two = h2(value);
	
	if (numElements == 0) 
		return -1;

	for(int i = 0; ;i++){
		int index = abs((hash_one + (i*hash_two)) % tableSize);
		if(table[index].elem == "" && table[index].deleted == false)
			return -1;
		if(table[index].elem == value && !table[index].deleted)
			return index;
	}
}

template <class T>
void HashTable<T>::insertIntoTable(T value, HashNode* &table){

	if(lambda() > 0.6)
		rehash();

	int hash_one = h1(value);
	int hash_two = h2(value);

	HashNode newItem;
	newItem.deleted = false;
	newItem.elem = value;

	bool flag = true;

	for(int i = 0; flag; i++){
		int index = abs((hash_one + (i*hash_two)) % tableSize);
		if((table[index].elem == "") || (table[index].deleted)){
			table[index] = newItem;
			++numElements;
			flag = false;
		}else if(table[index].elem == newItem.elem){
			flag = false;
		}
	}
}


//HASH FUNCTIONS//
//For my first hash function, I have chosen the classic DJB hash function
//created by Daniel Bernstein and first posted in the comp.lang.c newsgroup.
//The function multiplies each value by the constant 33 (using a bit shift for speed)
//and is one of the most efficient hashing algorithms that provides good spread
//for the second hash function, I simply took the first one and used a slightly
//modified technique
template <class T>
int HashTable<T>::h1(T elem){
	 int hash = 5381;
   for(int i = 0; i < elem.length(); i++)
      hash = ((hash << 5) + hash) + elem[i];
   return hash;
}

template <class T>
int HashTable<T>::h2(T elem){
	int hash = 773;
	for(int i =0; i < elem.length(); i++)
		hash = ((hash << 3) + hash) + 1 + elem[i];
	return hash;
}

template <class T>
void HashTable<T>::rehash(){

	numElements = 0;
	int old = tableSize;
	tableSize = tableSize*2 + 1;
	HashNode* newTable = new HashNode[tableSize];
	for(int i =0; i < old;i++)
		if(table[i].elem != "" && !table[i].deleted)
			insertIntoTable(table[i].elem,newTable);
	
	delete [] table;
	table = newTable;
	newTable = NULL;
	delete newTable;
}

