#ifndef SEARCHABLE_ADT_H
#define SEARCHABLE_ADT_H

#include <string>

using namespace std;

template <typename T>
class SearchableADT{

	public:
		virtual int loadFromFile(string filename) = 0;
		virtual void clear() = 0;
		virtual void insertEntry(T value) = 0;
		virtual void deleteEntry(T value) = 0;
		virtual bool isThere(T value) = 0;
		virtual int numEntries() = 0;
};

#endif
