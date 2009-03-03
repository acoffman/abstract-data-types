#ifndef AVL_H
#define AVL_H

#include "SearchableADT.h"

using namespace std;

template <typename T>
class AVL : public SearchableADT<T>{

	private:
		struct Node{
			T element;
			Node* left;
			Node* right;
			short deltaHeight;
		};

		Node* root;
		int numNodes;

		Node* getNode(T elem){
			Node* temp;
			temp->left = temp->right = NULL;
			temp->element = elem;
			temp->deltaHeight = 0;
			return temp;
		};

			int height(Node *rt) const;
			bool findHelper(Node* rt, T val);
			void insertHelper(T val, Node* &rt);
			void clearHelper(Node* rt);
			void cloneHelper(Node* thisTree, Node* originalTree);
			Node* findMin(Node* rt) const;
			void rotateWithLeftChild(Node* &rt);
			void rotateWithRightChild(Node* &rt);
			void doubleRotateWithLeftChild(Node* &rt);
			void doubleRotateWithRightChild(Node* &rt);
			int max(int arg1, int arg2);

		public:
			AVL();
			~AVL();
			AVL(const AVL<T> &avl);
			void insertEntry(T value);
			void deleteEntry(T value);
			bool isThere(T value);
			void clear();
			void clone(AVL<T>* rt);
			int numEntries();
			int loadFromFile(string filename);
};

#include "AVL.cpp"

#endif
