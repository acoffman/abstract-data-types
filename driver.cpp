#include <ctime>
#include <iostream>
#include "BST.cpp"

using namespace std;

int main(int agvc, char* argvc[]){
	
	clock_t start, finish;

	start = clock();

	//do some work
	SearchableADT<int> *test = new BST<int>;
	
	test->insertEntry(1);
	test->insertEntry(2);
	test->insertEntry(3);
	test->insertEntry(0);
	test->insertEntry(-5);
	 
 cout << endl << test->numEntries();

	cout << test->isThere(-5);
	cout << test->isThere(3);
	cout << test->isThere(1);
	cout << test->isThere(-15);


	test->clear();

	cout << endl << test->numEntries();
	
	cout << test->isThere(1);

	finish = clock();

	cout << "time: "
		<< ((double)(finish - start)/CLOCKS_PER_SEC)
		<< endl;
	
	return 0;
}
