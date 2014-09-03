/******************************************************************************

Project: DataStructures-Algorithms_Practice
File: DataStructures/Linear/Stack/Stack.h
Programmer: David Frye
Description: This file contains the class declaration/definition for a stack 
	ADT, implemented atop a linked list data structure.

******************************************************************************/

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "LinkedList/LinkedList.h"

//  Class: Stack
//  A templated stack class. Builds upon the linear linked list data structure 
// to provide a last-in-first-out (LIFO) abstract data type (ADT).
template<class T>
class Stack
{
	public:

		// Default constructor.
		Stack() {};

		// Pushes "value" onto the stack.
		void push(T value)
		{
			list.prepend(value);
		}

		// Pops the top value from the stack.
		T pop()
		{
			T value = top();

			list.deleteByIndex(0);

			return value;
		}

		// Returns the top value without popping it off the stack.
		T top() { return list.findValueByIndex(0); }

		// Prints the entire contents of the stack to stdout.
		void printStack() { list.printList(); }

		// Returns a boolean denoting whether or not the stack is empty.
		bool isEmpty() { return list.isEmpty(); }

		// Returns the current number of nodes on the stack.
		int getSize() { return list.getSize(); }

	protected:

		// The linked list used to implement the stack.
		LinkedList<T> list;
};

#endif // STACK_H