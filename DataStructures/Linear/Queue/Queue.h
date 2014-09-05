/******************************************************************************

Project: DataStructures-Algorithms_Practice
File: DataStructures/Linear/Queue/Queue.h
Programmer: David Frye
Description: This file contains the class declaration/definition for a queue 
	ADT, implemented atop a linked list data structure.

******************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include "../LinkedList/LinkedList.h"

//  Class: Queue
//  A templated queue class. Builds upon the linear linked list data structure 
// to provide a first-in-first-out (FIFO) abstract data type (ADT).
template<class T>
class Queue
{
	public:

		// Default constructor.
		Queue() {};

		// Enqueues "value" into the queue.
		void enqueue(T value)
		{
			list.append(value);
		}

		// Dequeues the eldest value from of the queue.
		T dequeue()
		{
			T value = top();

			list.deleteByIndex(0);

			return value;
		}

		// Returns the eldest value without dequeueing it from the queue.
		T top() { return list.findValueByIndex(0); }

		// Prints the entire contents of the queue to stdout.
		void printQueue() { list.printList(); }

		// Returns a boolean denoting whether or not the queue is empty.
		bool isEmpty() { return list.isEmpty(); }
		
		// Returns the current number of nodes in the queue.
		int getSize() { return list.getSize(); }

	protected:

		// The linked list used to implement the queue.
		LinkedList<T> list;
};

#endif // QUEUE_H