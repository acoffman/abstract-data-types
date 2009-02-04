#include <ctime>
#include <iostream>
#include "AVL.h"

using namespace std;

int main(int agvc, char* argvc[]){
	
	clock_t start, finish;

	start = clock();

	//do some work
	//SearchableADT<int> *test = new BST<int>;

	finish = clock();

	cout << "time: "
		<< ((double)(finish - start)/CLOCKS_PER_SEC)
		<< endl;
	
	return 0;
}
