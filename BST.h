#include "SearchableADT.h"

using namespace std;

template <typename T>
class BST : public SearchableADT<T>{

	public:
		BST();
		~BST();
		BST(const BST* bst);
		int loadFromFile(string filename);
		void clear();
		virtual void insertEntry(T value);
		virtual void deleteEntry(T value);
		bool isThere(T value);
		int numEntries();
		void clone(const BST* bst);

		const BST* operator=(const BST* bst);
	
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
};

