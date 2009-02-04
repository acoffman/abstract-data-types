#include "BST.h"

using namespace std;

template <typename T>
class AVL : public BST<T>{

	public:
		void insertEntry(T value);
		void deleteEntry(T value);

	private:
		struct Node{
			T element;
			Node* left, right;
			short deltaHeight;
		};

};
