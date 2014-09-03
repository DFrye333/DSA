/******************************************************************************

Project: DataStructures-Algorithms_Practice
File: DataStructures/Linear/LinkedList/LinkedList.h
Programmer: David Frye
Description: This file contains the class declaration/definition for a linked 
	list data structure. It serves as the basis for several ADTs
	(queue/stack, etc.).

******************************************************************************/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "LLNode.h"

//  Class: LinkedList
//  A templated linked list class. Builds upon the linked list node to create 
// a linked list (currently doubly-linked).
template<class T>
class LinkedList
{
	public:

		// Default constructor.
		LinkedList() { head = NULL; tail = NULL; size = 0; }
		
		// Construct list given an initial value.
		LinkedList(const T value)
		{
			size = 0;

			append(value);
		}

		// Construct list given multiple in-order initialization values.
		LinkedList(const T values[], const int count)
		{
			size = 0;

			for (int i = 0; i < count; ++i)
			{
				append(values[i]);
			}
		}

		// Destructor.
		~LinkedList()
		{
			// Delete head node until no head nodes remain (list is empty).
			while (!isEmpty())
			{
				deleteByIndex(0);
			}
		}

		// Inserts a new LLNode at some index of the list, given a value and an index.
		void insert(const T value, const int index)
		{
			// If the new node should be inserted at the beginning of the list, update the head pointer.
			if (head == NULL || index <= 0)
			{
				LLNode<T>* newNode = new LLNode<T>(value, head, NULL);
				if (head == NULL)
				{
					head = newNode;
				}
				else
				{
					head->setPrev(newNode);
					head = head->getPrev();
				}
				++size;

				// If list was empty before this insertion, update tail pointer.
				if (size == 1)
				{
					tail = head;
				}

				return;
			}

			// If the new node should be inserted at the end of the list, update the tail pointer.
			else if (index >= size)
			{
				tail->setNext(new LLNode<T>(value, NULL, tail));
				tail = tail->getNext();
				++size;

				return;
			}

			// Find the node before the target index, starting from the end of the list nearest the target.
			LLNode<T>* current = NULL;
			// If the target index is nearer to the head pointer, move in from the beginning of the list.
			if (index < ((size - 1) - index))
			{
				current = head;
				for (int i = 0; i < index && current->getNext() != NULL; ++i)
				{
					current = current->getNext();
				}

				// Insert new node at target index.
				LLNode<T>* newNode = new LLNode<T>(value, current->getNext(), current);
				current->getNext()->setPrev(newNode);
				current->setNext(newNode);
			}
			// If the target index is nearer to the tail pointer, move in from the end of the list.
			else
			{
				current = tail;
				for (int i = size - 1; i > index && current->getPrev() != NULL; --i)
				{
					current = current->getPrev();
				}

				// Insert new node at target index.
				LLNode<T>* newNode = new LLNode<T>(value, current, current->getPrev());
				current->getPrev()->setNext(newNode);
				current->setPrev(newNode);
			}
			++size;

			// If the new node was inserted at the end of the list, update the tail pointer.
			if (index >= (size - 1))
			{
				tail = current->getNext();
			}
		}

		// Inserts a new LLNode at the beginning of the list, given a value.
		void prepend(const T value)
		{
			insert(value, 0);
		}

		// Inserts a new LLNode at the end of the list, given a value.
		void append(const T value)
		{
			insert(value, size);
		}

		// Deletes a LLNode from the list, given an index.
		bool deleteByIndex(const int index)
		{
			// Ensure that list is not empty.
			if (head == NULL || tail == NULL)
			{
				return false;
			}

			// Target node is at the beginning of the list.
			if (index <= 0)
			{
				// Delete head node and update head pointer.
				LLNode<T>* next = head->getNext();
				delete head;
				--size;
				head = next;

				// If the list now contains a single node, the head and tail pointers point to the same node.
				if (size <= 1)
				{
					tail = head;
				}

				return true;
			}

			// Target node is at the end of the list.
			else if (index >= (size - 1))
			{
				LLNode<T>* prev = tail->getPrev();
				tail->getPrev()->setNext(NULL);
				delete tail;
				--size;
				tail = prev;

				return true;
			}

			// Find the target node, starting at the end of the list nearest the target node.
			LLNode<T>* trailing = NULL;
			LLNode<T>* leading = NULL;
			LLNode<T>* toDelete = NULL;
			// If the target node is nearer to the head pointer, move in from the beginning of the list.
			if (index < ((size - 1) - index))
			{
				trailing = head;
				leading = head;
				for (int i = 0; i < index && leading->getNext() != NULL; ++i)
				{
					trailing = leading;
					leading = leading->getNext();
				}

				// Remove the target node from the list.
				toDelete = leading;
				trailing->setNext(leading->getNext());
				leading->getNext()->setPrev(trailing);
			}
			// If the target node is nearer to the tail pointer, move in from the end of the list.
			else
			{
				trailing = tail;
				leading = tail;
				for (int i = size - 1; i > index && leading->getPrev() != NULL; --i)
				{
					trailing = leading;
					leading = leading->getPrev();
				}

				// Remove the target node from the list.
				toDelete = leading;
				trailing->setPrev(leading->getPrev());
				leading->getPrev()->setNext(trailing);
			}
			delete toDelete;
			--size;

			// If the node was deleted from the end of the list, update the tail pointer.
			if (index >= size)
			{
				tail = trailing;
			}

			return true;
		}

		// Find the value of the LLNode in the list that corresponds to the given index.
		T findValueByIndex(const int index)
		{
			if (head == NULL)
			{
				return NULL;
			}

			LLNode<T>* current = head;

			for (int i = 0; i < index; ++i)
			{
				if (current == NULL)
				{
					return NULL;
				}

				current = current->getNext();
			}

			return current->getData();
		}

		// Print the entire list in-order.
		void printList()
		{
			LLNode<T>* current = head;

			while (current != NULL)
			{
				std::cout << current->getData();
				if (current->getNext() != NULL)
				{
					std::cout << " <-> ";
				}
				current = current->getNext();
			}
			std::cout << std::endl;

			std::cout << "Size: " << size << std::endl;
			std::cout << "Head value: " << head->getData() << std::endl;
			std::cout << "Tail value: " << tail->getData() << std::endl;
			std::cout << std::endl;
		}
		
		// Reverse the ordering of the list.
		void reverseList()
		{
			// Reverse singly-linked list.
			/*LLNode<T>* trailing = NULL;
			LLNode<T>* middle = head;
			LLNode<T>* leading = NULL;

			while (middle != NULL)
			{
				leading = middle->getNext();
				middle->setNext(trailing);
				trailing = middle;
				middle = leading;
			}

			head = trailing;*/

			// Reverse doubly-linked list.
			LLNode<T>* current = head;
			LLNode<T>* temp = NULL;
			while (current != NULL)
			{
				temp = current->getNext();
				current->setNext(current->getPrev());
				current->setPrev(temp);
				current = current->getPrev();
			}
			
			temp = tail;
			tail = head;
			head = temp;
		}

		// Provides the current number of nodes in the list.
		int getSize() { return size; }

		// Returns a boolean denoting whether or not the list is empty.
		bool isEmpty() { return (size == 0); }

	protected:

		// A pointer to the head LLNode of the list.
		LLNode<T>* head;

		// A pointer to the tail LLNode of the list.
		LLNode<T>* tail;

		// The size of the list.
		int size;
};

#endif // LINKEDLIST_H