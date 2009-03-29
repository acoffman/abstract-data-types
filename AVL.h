/******************************
 * Author: Adam Coffman
 *
 * Filename: AVL.h
 *
 * Description: This is the header file for the AVL Tree 
 * 	It contains variables and function protoypes
 * 
 * Build Instructions: A makefile is included in the project directory
 * 	program can be run as ./driver
 *
 * 	CITATION: Much of the code for the AVL was taken or adapted from the text book
 ******************************/

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
			temp = new Node;
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
			int heightHelper(Node* rt);
			void deleteHelper(T &value, Node* &rt);

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
			int treeHeight();
			int  tableCapacity(){return -1;}; 
};

#include "AVL.cpp"

#endif
