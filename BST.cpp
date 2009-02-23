#include "BST.h"
#include <iostream>
using namespace std;
//CLEAR AND HELPER//
template <class T>
void BST<T>::clear(){
	clearHelper(root);
	root = NULL;
	numNodes = 0;
}

template <class T>
void BST<T>::clearHelper(Node* rt){
	if(rt->right != NULL)
		clearHelper(rt->right);
	if(rt->left != NULL)
		clearHelper(rt->left);
	delete rt;
}
//*****************//


//FIND AND HELPER///
template <class T>
bool BST<T>::isThere(T value){
	return findHelper(root, value);
}

template <class T>
bool BST<T>::findHelper(Node* rt, T elem){
	if(rt == NULL)
		return false;
	else if(elem < rt->element)
		return findHelper(rt->left, elem);
	else if(elem > rt->element)
		return findHelper(rt->right, elem);
	else return true;
}
//*******************//


//INSERT AND HELPER//
template <class T>
void BST<T>::insertEntry(T value){
	insertHelper(root,getNode(value));
}

template <class T>
void BST<T>::insertHelper(Node* &rt, Node* newNode){
	if(rt == NULL){
		rt = newNode;
		++numNodes;
	}
	else if(newNode->element < rt->element)
		insertHelper(rt->left, newNode);
	else if(newNode->element > rt->element)
		insertHelper(rt->right, newNode);
}
//********************//


//CONSTRUCTORS AND DESTRUCTOR//
template <class T>
BST<T>::~BST(){
	clear();
};

template <class T>
BST<T>::BST(){
	root = NULL;
}

template <class T>
BST<T>::BST(const BST* bst){
	clone(bst);
}
//******************//

//DELETE FUNCTIONS//
template <class T>
void BST<T>::deleteEntry(T value){
	return;
}

//****************//

//MISC FUNCTIONS//
template <class T>
int BST<T>::numEntries(){
	return numNodes;
}

template <class T>
void BST<T>::clone(const BST* bst){
	cloneHelper(root, bst.root);
}

template <class T>
void BST<T>::cloneHelper(Node* thisTree, Node* originalTree){
	thisTree = getNode(originalTree->element);
	if(originalTree->left != NULL)
		cloneHelper(thisTree->left, originalTree->left);
	if(originalTree->right != NULL)
		cloneHelper(thisTree->right, originalTree->right);
}

template <class T>
int BST<T>::loadFromFile(string filename){
	return 0;
}


