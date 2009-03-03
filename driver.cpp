#include <ctime>
#include <iostream>
#include "SearchableADT.h"
#include "BST.h"
#include "AVL.h"

using namespace std;

int main(int agvc, char* argvc[]){
	
	clock_t start, finish;

	start = clock();

	//do some work
	SearchableADT<int> *test = new AVL<int>;
	
	test->insertEntry(1);
	//test->insertEntry(2);
	//test->insertEntry(3);
	//test->insertEntry(0);
	//test->insertEntry(-5);
	 
 	cout << endl << test->numEntries();


	//test->deleteEntry(0);
	cout << test->numEntries();

	cout << endl << test->isThere(0);

	//test->deleteEntry(-5);

	cout << endl << test->isThere(-5);
	cout << endl << test->isThere(1);

	//cout << endl << test->numEntries();

	finish = clock();

	cout << "time: "
		<< ((double)(finish - start)/CLOCKS_PER_SEC)
		<< endl;
	
	return 0;
}
