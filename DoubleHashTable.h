#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count; //number of elements currently in the hash table
		int power; //array_size = 2^power
		int array_size; 
		T *array; //An array of objects of type T
		state *array_state; // State of the array (EMPTY, OCCUPIED OR DELETED)

		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
	clear();
	delete[] array;
	delete[] array_state;
}

template<typename T >
int DoubleHashTable<T >::size() const {
	return count;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
	int capacity = pow(2, power);
	return capacity;
}

template<typename T >
bool DoubleHashTable<T >::empty() const {
	int capacityTable = capacity();
	for(int i = 0; i < capacityTable; i++){
		if(array_state[i] != EMPTY){
			return false;
		}
	}
	return true;
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
	int amount = capacity();
	int hashOne = obj%amount;
	while(hashOne < 0){
		hashOne=hashOne+amount;
	}
	return hashOne;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
	int amount = capacity();
	int partOne = obj/amount;
	int hashTwo = partOne%amount;
	if(hashTwo%2 == 0){
		hashTwo++;
	}
	return hashTwo;
}

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
	int capacityTable = capacity();
	for(int i = 0; i <= capacityTable; i++){
		if(array_state[i] == obj){
			return true;
		}
	}	
	return false;
}

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {      
     return array[n];              
}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
	int amount = capacity();
	int number = size();
	if(amount == number){
		throw overflow();
	}
	int operandOne = h1(obj);
	int operandTwo = h2(obj);
	int i = 0;
	int hashFunction = obj%amount;
	while(array_state[hashFunction] == OCCUPIED){
		i++;
		hashFunction = (operandOne + i*operandTwo)%amount;
	}
	if (i == 0){
		hashFunction = operandOne;
	}
	array[hashFunction] = obj;
	array_state[hashFunction] = OCCUPIED;
	count++;
	return;
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
	int amount = capacity();
	for(int i = 0; i < amount; i++){
		if(array[i] == obj){
			array[i] = 0;
			array_state[i] = DELETED;
			count--;
			return true;
		}
	}
	return false;
}

template<typename T >
void DoubleHashTable<T >::clear() {
	int amount = capacity(); 
	for(int i = 0; i < amount; i++){
		array[i] = 0;
		array_state[i] = EMPTY;
		count--;
	}
	return ; 
}

template<typename T >
void DoubleHashTable<T >::print() const {
      //  A function you can use to print the class for debugging purposes
	  //  This function will not be tested.
	return;
}

#endif