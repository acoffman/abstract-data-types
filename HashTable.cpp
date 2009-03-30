
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
	numEntries = 0;
	tableSize = 0;
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
	int hash_one = h1(value);
	HashNode newItem;
	newItem.deleted = false;
	*(newItem.elem) = value;
	if (is_empty(hash_one % tableSize)){
		table[hash_one % tableSize] = newItem;	
	}else{
		int hash_two = h2(value);
		for(int i = 1, flag = true; flag; i++){
			if(is_empty((hash_one + i*hash_two) % tableSize)){
				table[(hash_one + i*hash_two) % tableSize] = newItem;
				flag = false;
			}else if(table[(hash_one + i*hash_two) % tableSize].elem == newItem.elem)
				flag = false;
		}
	}
}

template <class T>
void HashTable<T>::deleteEntry(T value){
	int index = search(value);
	if(index != -1)
		table[index].deleted = true;
}

template <class T>
int HashTable<T>::search(T value){
	int hash_one = h1(value);
	int hash_two = h2(value);
	int hashval = hash_one;
	
	while(((*table[hashval % tableSize].elem) != value) && (!should_stop(hashval % tableSize))){
		hashval += hash_two;
	}

	if(!should_stop(hashval)){
		return hashval % tableSize;
	}
	return -1;
}


//HASH FUNCTIONS//
//For my first hash function, I have chosen the classic DJB hash function
//created by Daniel Bernstein and first posted in the comp.lang.c newsgroup.
//The function multiplies each value by the constant 33 (using a bit shift for speed)
//and is one of the most efficient hashing algorithms that provides good spread
template <class T>
int HashTable<T>::h1(T elem){
	 unsigned int hash = 5381;
   for(int i = 0; i < elem.length(); i++)
      hash = ((hash << 5) + hash) + elem[i];
   
   return hash;
}





