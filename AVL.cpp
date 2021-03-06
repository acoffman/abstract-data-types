/******************************
 * Author: Adam Coffman
 *
 * Filename: AVL.cpp
 *
 * Description: This is the implementation file for the Binary 
 * Search Tree. It contains function definitions.
 * 
 * Build Instructions: A makefile is included in the project directory
 * 	program can be run as ./driver
 ******************************/

#include <iostream>

//FIND FUNCTIONS//
template <class T>
bool AVL<T>::isThere(T val){
	return findHelper(root, val);
}

template <class T>
bool AVL<T>::findHelper(Node* rt, T val){
	if(rt == NULL)
		return false;
	else if(val < rt->element)
		return findHelper(rt->left, val);
	else if(val> rt->element)
		return findHelper(rt->right, val);
	else return true;
}
//***************//


//INSERT FUNCTIONS//
template <class T>
void AVL<T>::insertEntry(T val){
	insertHelper(val, root);	
}

template <class T>
void AVL<T>::insertHelper(T val, Node* &rt){
 if(rt == NULL){
		rt = getNode(val);
		numNodes++;
	}else if(val < rt->element){
		insertHelper(val, rt->left);
		if(height(rt->left) - height(rt->right) == 2)
			if(val < rt->left->element)
				rotateWithLeftChild(rt);
			else 
				doubleRotateWithLeftChild(rt);
	}else if(val > rt->element){
		insertHelper(val, rt->right);
		if(height(rt->right) - height(rt->left) == 2)
			if(rt->right->element < val)
				rotateWithRightChild(rt);
			else
				doubleRotateWithRightChild(rt);
	}
	rt->deltaHeight = max(height(rt->left), height(rt->right)) + 1;
}
//*******************//


//CLEAR AND HELPER//
template <class T>
void AVL<T>::clear(){
	clearHelper(root);
	root = NULL;
	numNodes = 0;
}

template <class T>
void AVL<T>::clearHelper(Node* rt){
	if(rt->right != NULL)
		clearHelper(rt->right);
	if(rt->left != NULL)
		clearHelper(rt->left);
	delete rt;
}
//*****************//


//CLONE FUNCTIONS//
template <class T>
void AVL<T>::clone(AVL* avl){
	cloneHelper(root, avl.root);
}

template <class T>
void AVL<T>::cloneHelper(Node* thisTree, Node* originalTree){
	thisTree = getNode(originalTree->element);
	if(originalTree->left != NULL)
		cloneHelper(thisTree->left, originalTree->left);
	if(originalTree->right != NULL)
		cloneHelper(thisTree->right, originalTree->right);
}
//*****************//


//CONSTRUCTORS AND DESTRUCTORS//
template <class T>
AVL<T>::~AVL(){
	clear();
};

template <class T>
AVL<T>::AVL(){
	root = NULL;
	numNodes = 0;
}

template <class T>
AVL<T>::AVL(const AVL<T> &avl){
	clone(avl);
}
//**************************//

//ROTATION FUNCTIONS//
template <class T>
void AVL<T>::rotateWithLeftChild(Node* &rt){
	Node* n1 = rt->left;
	rt->left = n1->right;
	n1->right = rt;
	rt->deltaHeight = max(height(rt->left), height(rt->right)) + 1;
	n1->deltaHeight = max(height(n1->left), rt->deltaHeight) +1;
	rt = n1;
}

template <class T>
void AVL<T>::rotateWithRightChild(Node* &rt){
	Node* n1 = rt->right;
	rt->right = n1->left;
	n1->left = rt;
	rt->deltaHeight = max(height(rt->left), height(rt->right)) +1;
	n1->deltaHeight = max(height(n1->right), rt->deltaHeight) +1;
	rt = n1;
}

template <class T>
void AVL<T>::doubleRotateWithLeftChild(Node* &rt){
	rotateWithRightChild(rt->left);
	rotateWithLeftChild(rt);
}

template <class T>
void AVL<T>::doubleRotateWithRightChild(Node* &rt){
	rotateWithLeftChild(rt->right);
	rotateWithRightChild(rt);
}
//****************//


//HELPER FUNCTIONS//
template <class T>
int AVL<T>::max(int arg1, int arg2){
	return arg1 >= arg2 ? arg1 : arg2;
}

template <class T>
int AVL<T>::height(Node *rt) const{
	return rt == NULL ? -1 : rt->deltaHeight;
}

template <class T>
int AVL<T>::numEntries(){
	return numNodes;
}

template <class T>
int AVL<T>::loadFromFile(string filename){
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

template <class T>
typename AVL<T>::Node* AVL<T>::findMin(Node* rt) const{
	if(rt == NULL)
		return NULL;
	if(rt->left == NULL)
		return rt;
	return findMin(rt->left);
}

//TREE HEIGHT AND HELPER//
template <class T>
int AVL<T>::treeHeight(){
	return heightHelper(root);
}

template <class T>
int AVL<T>::heightHelper(Node* rt){
	if(rt == NULL)
		return 0;
	else{
		int height, height_left, height_right;
		height_left = heightHelper(rt->left);
		height_right = heightHelper(rt->right);
		height = height_right > height_left ? height_right : height_left;
		return height + 1;
	}
}

//DELETE FUNCTION AND HELPER//
template <class T>
void AVL<T>::deleteEntry(T value){
		deleteHelper(value, root);
}

template <class T>
void AVL<T>::deleteHelper(T &value, Node* &rt){
	if(rt == NULL)
		return;
	else if (value < rt->element){
		deleteHelper(value, rt->left);
		if(height(rt->right) - height(rt->left) == 2){
			if(rt->right->right == NULL)
				doubleRotateWithRightChild(rt);
			else
				rotateWithRightChild(rt);
		}
		rt->deltaHeight = max(height(rt->left), height(rt->right)) +1;
	}
	else if (value > rt->element){
		deleteHelper(value, rt->right);
		if(height(rt->left) - height(rt->right) == 2){
			if(rt->left->right == NULL)
				doubleRotateWithLeftChild(rt);
			else
				rotateWithLeftChild(rt);
		}
		rt->deltaHeight = max(height(rt->left),height(rt->right)) + 1;
	}
	else if(rt->left != NULL && rt->right != NULL){
		rt->element = findMin(rt->right)->element;
		deleteHelper(rt->element, rt->right);
	}
	else{
		Node* old = rt;
		rt = (rt->left != NULL) ? rt->left : rt->right;
		delete old;
		numNodes--;
	}
}
//****************//
