#ifndef BTNODE_H
#define BTNODE_H

//  Class: BTNode
//  A templated binary tree node class. Acts as the building block for the 
// binary tree classes and, in turn, several tree data structures
// (BST/Trie, etc.).
template<class T>
class BTNode
{
	public:

		// Default constructor.
		BTNode() { left = NULL; right = NULL; parent = NULL; }

		// Alternative constructor for when provided with only a piece of data.
		BTNode(T d) { data = d; left = NULL; right = NULL; parent = NULL; }

		// Alternative constructor for when provided with a piece of data and a parent node.
		BTNode(T d, BTNode<T>* p) { data = d; left = NULL; right = NULL; parent = p; }

		// Returns the data for this node.
		T getData() { return data; }

		// Returns the left child for this node.
		BTNode* getLeft() { return left; }

		// Returns the right child for this node.
		BTNode* getRight() { return right; }

		// Returns the parent for this node.
		BTNode* getParent() { return parent; }

		// Sets the data for this node.
		void setData(T d) { data = d; }

		// Sets the left child for this node.
		void setLeft(BTNode* l) { left = l; }

		// Sets the right child for this node.
		void setRight(BTNode* r) { right = r; }

		// Sets the parent for this node.
		void setParent(BTNode* p) { parent = p; }

	protected:

		// This node's left child node.
		BTNode* left;

		// This node's right child node.
		BTNode* right;

		// This node's parent node.
		BTNode* parent;

		// This node's data.
		T data;
};

#endif // BTNODE_H