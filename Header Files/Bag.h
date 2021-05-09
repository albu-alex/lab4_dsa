#pragma once
//DO NOT INCLUDE BAGITERATOR
typedef int TElem;

class Node{
    public:
        TElem element;
        int frequency=0;
        Node* next;
};

class SLL{
    public:
        Node* head;
};

//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111
#define INITIAL_CAPACITY 11
class BagIterator; 
class Bag {
private:
	SLL* hash_table;
	int divisor;
	int length;
	int capacity;

	//DO NOT CHANGE THIS PART
	friend class BagIterator;
public:
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appearch is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	//resizes the dynamically allocated hash table
	void resize();

	//destructor
	~Bag();
};