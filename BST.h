/******************************
 * Author: Adam Coffman
 *
 * Filename: BST.h
 *
 * Description: This is the header file for the Binary 
 * Search Tree. It contains variables and function protoypes
 * 
 * Build Instructions: A makefile is included in the project directory
 * 	program can be run as ./driver
 *
 * 	CITATION: Much of the code for the BST was taken or adapted from the text book
 ******************************/
#ifndef BST_H
#define BST_H

#include "SearchableADT.h"

using namespace std;

template <typename T>
class BST : public SearchableADT<T>{

	public:
		BST();
		~BST();
		BST(const BST<T> &bst);
		int loadFromFile(string filename);
		void clear();
		void insertEntry(T value);
		void deleteEntry(T value);
		bool isThere(T value);
		int numEntries();
		void clone(const BST* bst);

	
	private:
		struct Node {
			T element;
			Node *left, *right;	
		};

		Node* getNode(T elem){
			Node* temp;
			temp = new Node;
			temp->left = temp->right = NULL;
			temp->element = elem;
			return temp;
		};

		Node *root;

	protected:
		int numNodes;
		void clearHelper(Node* rt);
		void insertHelper(Node* &rt, Node* newNode);
		bool findHelper(Node* rt, T elem);
		void cloneHelper(Node* thisTree, Node* originalTree);
		void deleteHelper(T &value, Node* &rt);
		Node* findMin(Node* t) const;
};

#include "BST.cpp"

#endif

