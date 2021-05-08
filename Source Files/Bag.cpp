#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	this->length=0;
	this->capacity=INITIAL_CAPACITY;
    this->hash_table = new Node*[INITIAL_CAPACITY];
	for(int i=0;i<INITIAL_CAPACITY;i++){
	    this->hash_table[i] = new Node[INITIAL_CAPACITY];
	}
    this->divisor = INITIAL_CAPACITY;
}


void Bag::add(TElem elem) {
	if(this->length==this->capacity-1){
	    resize();
	}
	int i=0;
	while(i<this->capacity && this->hash_table[elem%this->divisor][i].element!=-1){
	    i++;
	}
	this->length++;
}

void Bag::resize() {
    return;
}

bool Bag::remove(TElem elem) {
	//TODO - Implementation
	return false; 
}


bool Bag::search(TElem elem) const {
	//TODO - Implementation
	return false; 
}

int Bag::nrOccurrences(TElem elem) const {
	//TODO - Implementation
	return 0; 
}


int Bag::size() const {
	return this->length;
}
//Complexity: Theta(1)

bool Bag::isEmpty() const {
    if(this->length==0)
        return true;
    return false;
}
//Complexity: Theta(1)

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
	for(int i=0;i<this->capacity;i++){
	    delete[] this->hash_table[i];
	}
	delete[] this->hash_table;
}
//Complexity: Theta(n)

