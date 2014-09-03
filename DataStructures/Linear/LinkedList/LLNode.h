/******************************************************************************

Project: DataStructures-Algorithms_Practice
File: DataStructures/Linear/LinkedList/LLNode.h
Programmer: David Frye
Description: This file contains the class declaration/definition for a linked 
	list node. It serves as the basis for the linked list data structure.

******************************************************************************/

#ifndef LLNode_H
#define LLNode_H

#include <iostream>

//  Class: LLNode
//  A templated linked list node class. Acts as the building block for the 
// linked list class and, in turn, several linear data structures
// (queue/stack, etc.).
template<class T>
class LLNode
{
	public:

		// Default constructor.
		LLNode() { next = NULL; prev = NULL; }

		// Alternative constructor for when provided with only a piece of data.
		LLNode(T d) { data = d; next = NULL; prev = NULL; }

		//  Alternative constructor for when provided with a piece of data and 
		// a next node.
		LLNode(T d, LLNode<T>* n) { data = d; next = n; prev = NULL; }

		//  Alternative constructor for when provided with a piece of data and 
		// both next and previous pointers.
		LLNode(T d, LLNode<T>* n, LLNode<T>* p) { data = d; next = n; prev = p; }

		// Returns the next node for this node.
		LLNode<T>* getNext() { return next; }

		// Returns the previous node for this node.
		LLNode<T>* getPrev() { return prev; }

		// Returns the data for this node.
		T getData() { return data; }

		// Sets the next node for this node.
		void setNext(LLNode<T>* n) { next = n; }

		// Sets the previous node for this node.
		void setPrev(LLNode<T>* p) { prev = p; }

		// Sets the data for this node.
		void setData(T d) { data = d; }

	protected:
		
		// This node's next node.
		LLNode<T>* next;

		// This node's previous node.
		LLNode<T>* prev;

		// This node's data.
		T data;
};

#endif // LLNode_H