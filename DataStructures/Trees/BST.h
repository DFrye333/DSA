#ifndef BST_H
#define BST_H

#include <iostream>

#include "BTNode.h"
#include "../Linear/Stack/Stack.h"
#include "../Linear/Queue/Queue.h"

//  Class: BST
//  A templated linked list node class. Acts as the building block for the 
// linked list class and, in turn, several linear data structures
// (queue/stack, etc.).
template<class T>
class BST
{
	public:

		// Default constructor.
		BST() {};

		// Alternative constructor for when provided with an array of initial node values.
		BST(T values[], int count)
		{
			for (int i = 0; i < count; ++i)
			{
				insert(values[i]);
			}
		}

		// Insert a new node into the tree, given a value.
		void insert(T value)
		{
			// Insert node as root node in empty tree.
			if (root == NULL)
			{
				root = new BTNode<T>(value);
				return;
			}

			// Insert node into non-empty tree.
			BTNode<T>* parent = root;
			BTNode<T>* current = root;
			while (true)
			{
				parent = current;

				// Value should be inserted within left subtree of current node.
				if (value < current->getData())
				{
					// Continue traversing left subtree to find new leaf node position.
					if (current->getLeft() != NULL)
					{
						current = current->getLeft();
					}

					// Create new leaf node as the left child.
					else
					{
						current->setLeft(new BTNode<T>(value, parent));
						return;
					}
				}
				
				// Value should be inserted within right subtree of current node.
				else
				{
					// Continue traversing right subtree to find new leaf node position.
					if (current->getRight() != NULL)
					{
						current = current->getRight();
					}

					// Create new leaf node as the right child.
					else
					{
						current->setRight(new BTNode<T>(value, parent));
						return;
					}
				}
			}
		}

		// Delete a node from the tree, given a value.
		T deleteByValue(T value)
		{
			// Delete the node corresponding to the given value.
			return remove(searchByValue(value));
		}

		// Remove a node from the tree.
		T remove(BTNode<T>* node)
		{
			// Ensure that a null parameter has not been passed.
			if (node == NULL)
			{
				return NULL;
			}

			// The data from the removed/deleted node, to be returned.
			T removedData = NULL;

			// Grab current node's parent.
			BTNode<T>* parent = node->getParent();

			// If the node has no children, simply delete it.
			if (node->getLeft() == NULL && node->getRight() == NULL)
			{
				// If the current node has a parent, set its own pointer within that parent to null.
				if (parent != NULL && node == parent->getLeft())
				{
					parent->setLeft(NULL);
				}
				else if (parent != NULL && node == parent->getRight())
				{
					parent->setRight(NULL);
				}

				// If the current node has no parent and no children, it must be the root node.
				else
				{
					root = NULL;
				}

				// Grab the current node's data, then delete the current node.
				removedData = node->getData();
				delete node;
			}

			// If the node has only a left child, replace the current node with that child.
			else if (node->getLeft() != NULL && node->getRight() == NULL)
			{
				// Repair the severed child -> parent relationship.
				node->getLeft()->setParent(parent);
				
				// If the current node has a parent, repair the severed parent -> child relationship.
				if (parent != NULL)
				{
					node == parent->getLeft() ? parent->setLeft(node->getLeft()) : parent->setRight(node->getLeft());
				}

				// Grab the current node's data, then delete the current node.
				removedData = node->getData();
				delete node;
			}

			// If the node has only a right child, replace the current node with that child.
			else if (node->getRight() != NULL && node->getLeft() == NULL)
			{
				// Repair the severed child -> parent relationship.
				node->getRight()->setParent(parent);
				
				// If the current node has a parent, repair the severed parent -> child relationship.
				if (parent != NULL)
				{
					node == parent->getLeft() ? parent->setLeft(node->getRight()) : parent->setRight(node->getRight());
				}

				// Grab the current node's data, then delete the current node.
				removedData = node->getData();
				delete node;
			}

			// If the node has two children, replace the current node's data with that of its successor and call a recursive delete on the successor.
			else
			{
				// Grab the current node's data.
				removedData = node->getData();

				// Find the successor of the current node.
				BTNode<T>* successor = findSuccessor(node);

				// Because we have established that the current node has two children, if the successor is null we have a problem!
				if (successor != NULL)
				{
					// Replace the current node's data with that of its successor.
					node->setData(successor->getData());

					// Recursively delete the successor from the tree.
					remove(successor);
				}
			}

			// Return the data from the removed/deleted node.
			return removedData;
		}

		// Find the predecessor of a given node.
		BTNode<T>* findPredecessor(BTNode<T>* node)
		{
			// Start the search at the root of the current node's left subtree.
			BTNode<T>* current = node->getLeft();
			
			// If the target node has no left subtree, it must look to its ancestors for a predecessor.
			if (current == NULL)
			{
				// Grab the target node's parent.
				current = node->getParent();

				// Continue up the ancestory until either a predecessor is found, or it is determined that none exists.
				while ((current != NULL) && (node->getData() >= current->getData()))
				{
					current = current->getParent();
				}
			}

			// If the target node does have a left subtree, its predecessor is the right-most child of that subtree.
			else
			{
				// Find the left subtree's right-most child.
				while (current->getRight() != NULL)
				{
					current = current->getRight();
				}
			}

			// Return the node's predecessor.
			return current;
		}

		// Find the successor of a given node.
		BTNode<T>* findSuccessor(BTNode<T>* node)
		{
			// Start the search at the root of the current node's right subtree.
			BTNode<T>* current = node->getRight();

			// If the target node has no right subtree, it must look to its ancestors for a successor.
			if (current == NULL)
			{
				// Grab the target node's parent.
				current = node->getParent();

				// Continue up the ancestory until either a successor is found, or it is determined that none exists.
				while ((current != NULL) && (node->getData() < current->getData()))
				{
					current = current->getParent();
				}
			}

			// If the target node does have a right subtree, its successor is the left-most child of that subtree.
			else
			{
				// Find the right subtree's left-most child.
				while (current->getLeft() != NULL)
				{
					current = current->getLeft();
				}
			}

			// Return the node's successor.
			return current;
		}

		// Search the tree for a given value.
		BTNode<T>* searchByValue(T value)
		{
			// Start the search at the root node.
			BTNode<T>* current = root;

			// Traverse the tree in the appropriate direction, looking for the target value.
			while (current != NULL && current->getData() != value)
			{
				current = value < current->getData() ? current->getLeft() : current->getRight();
			}

			// Return either the target node or null.
			return current;
		}

		// Calculate the height of the tree, provided no node (root by default).
		int calculateHeight()
		{
			return calculateHeight(root);
		}

		// Calculate the height of the tree, provided a specific node.
		int calculateHeight(BTNode<T>* node)
		{
			if (node == NULL)
			{
				return -1;
			}

			return std::max(calculateHeight(node->getLeft()), calculateHeight(node->getRight())) + 1;
		}

		// Perform an in-order tree traversal (iteratively or recursively, as specified by the user).
		void traverseInOrder(bool recursive = true)
		{
			recursive == true ? traverseInOrderRecursive(root) : traverseInOrderIterative();
		}

		// Perform a recursive in-order tree traversal.
		void traverseInOrderRecursive(BTNode<T>* node)
		{
			// The end of a branch has been reached.
			if (node == NULL)
			{
				return;
			}

			// Traverse the left subtree.
			traverseInOrderRecursive(node->getLeft());

			// Visit the current node.
			traverseVisit(node);

			// Traverse the right subtree.
			traverseInOrderRecursive(node->getRight());
		}

		// Perform an iterative in-order tree traversal.
		void traverseInOrderIterative()
		{
			// The stack that will contain the nodes that need to be visited, in order.
			Stack<BTNode<T>*> nodeStack;

			// Begin traversal at the root node.
			BTNode<T>* node = root;

			// Traverse until all nodes have been visited.
			while (!nodeStack.isEmpty() || node != NULL)
			{
				// The end of a branch has not been reached.
				if (node != NULL)
				{
					// Push the current node onto the "to visit" stack and then travel down to the left child.
					nodeStack.push(node);
					node = node->getLeft();
				}

				// The end of a branch has been reached.
				else
				{
					// Visit the next node in line (the top of the stack) and then travel down to the right child.
					node = nodeStack.pop();
					traverseVisit(node);
					node = node->getRight();
				}
			}
		}

		// Visit the current node while traversing a tree.
		void traverseVisit(BTNode<T>* node)
		{
			std::cout << node->getData() << " -> ";
		}

		// Perform a breadth-first traversal of the tree.
		void BFS()
		{
			// The queue that will contain the nodes that need to be visited, in order.
			Queue<BTNode<T>*>* nodeQueue = new Queue<BTNode<T>*>();

			// Begin traversal at the root node.
			BTNode<T>* current = root;

			// Traverse until all nodes have been visited.
			while (current != NULL)
			{
				// Enqueue the left child, if one exists.
				if (current->getLeft() != NULL)
				{
					nodeQueue->enqueue(current->getLeft());
				}

				// Enqueue the right child, if one exists.
				if (current->getRight() != NULL)
				{
					nodeQueue->enqueue(current->getRight());
				}

				// Visit the current node.
				traverseVisit(current);

				// Visit the next node in line (the front of the queue).
				current = nodeQueue->dequeue();
			}
		}

	protected:

		// A pointer to the root BTNode of the tree.
		BTNode<T>* root;
};

#endif // BST_H