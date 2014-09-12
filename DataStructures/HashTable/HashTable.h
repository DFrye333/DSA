/******************************************************************************

Project: DataStructures-Algorithms_Practice
File: DataStructures/HashTable/HashTable.h
Programmer: David Frye
Description: This file contains the class declaration/definition for a hash 
	table data structure.

******************************************************************************/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <functional>

//  Class: HashTable
//  A templated hash table class. Currently implemented using a std::hash 
// object, but this could be replaced with another hash function if 
// desired.
template <class Key, class Value>
class HashTable
{
	public:

		// Default constructor.
		HashTable()
		{
			size = 100;
			table = new Value[size]();
		}

		// Alternative constructor for when provided with an initial size.
		HashTable(int s)
		{
			size = s;
			table = new Value[size]();
		}
		
		// Destructor.
		~HashTable()
		{
			// Delete the table.
			if (table)
			{
				delete[] table;
				table = NULL;
			}
		}

		// Returns the value of a given key.
		Value& operator[](Key key)
		{
			return table[hash(key)];
		}

		// Prints the contents of the hash table.
		void printHashTable()
		{
			for (int i = 0; i < size; ++i)
			{
				std::cout << "Table[" << i << "]:\t" << table[i] << std::endl;
			}
		}

	protected:

		// Calculate the hash of an input value.
		int hash(Key key)
		{
			return (hash_function(key) % size);
		}

		// The array that implements the table.
		Value* table;

		// The current size of the hash table.
		int size;

		// The hash function of the hash table.
		std::hash<Key> hash_function;
};

#endif // HASHTABLE_H