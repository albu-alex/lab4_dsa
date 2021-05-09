#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	this->length=0;
	this->capacity=INITIAL_CAPACITY;
    this->hash_table = new SLL[INITIAL_CAPACITY];
    for(int i=0;i<INITIAL_CAPACITY;i++)
        this->hash_table[i].head = nullptr;
    this->divisor = INITIAL_CAPACITY;
}


void Bag::add(TElem elem) {
	if(this->length==this->capacity-1){
	    resize();
	}
	int position=abs(elem%this->divisor);
	Node* new_element = new Node();
	new_element->frequency = 1;
	new_element->next = nullptr;
	new_element->element = elem;
	if(this->hash_table[position].head == nullptr){
	    this->hash_table[position].head = new_element;
	}
	else{
	    Node* current_element;
	    current_element = this->hash_table[position].head;
	    while(current_element != nullptr && current_element->element != elem)
            current_element = current_element->next;
	    if(current_element!= nullptr && current_element->element == elem)
        {
	        current_element->frequency++;
	        this->length++;
	        return;
        }
	    this->hash_table[position].head->next = this->hash_table[position].head;
	    this->hash_table[position].head = new_element;
	}
	this->length++;
}

void Bag::resize() {
    return;
}

bool Bag::remove(TElem elem) {
    int position=abs(elem%this->divisor);
    Node* current_element;
    Node* previous_element;
    current_element = this->hash_table[position].head;
    while(current_element != nullptr && current_element->element != elem) {
        previous_element = current_element;
        current_element = current_element->next;
    }
    if(current_element!= nullptr && current_element->element == elem)
    {
        if(current_element->frequency > 1) {
            current_element->frequency--;
            this->length--;
        }
        else{
            this->length--;
            previous_element->next = current_element->next;
        }
        return true;
    }
	return false; 
}


bool Bag::search(TElem elem) const {
    int position=abs(elem%this->divisor);
    Node* current_element;
    current_element = this->hash_table[position].head;
    while(current_element != nullptr && current_element->element != elem)
        current_element = current_element->next;
    if(current_element!= nullptr && current_element->element == elem)
	    return true;
    return false;
}

int Bag::nrOccurrences(TElem elem) const {
    int position=abs(elem%this->divisor);
    Node* current_element;
    current_element = this->hash_table[position].head;
    while(current_element != nullptr && current_element->element != elem)
        current_element = current_element->next;
    if(current_element!= nullptr && current_element->element == elem)
        return current_element->frequency;
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
//Complexity: Theta(bagiterator)

Bag::~Bag() {
	for(int i=0;i<this->capacity;i++){
	    delete this->hash_table[i].head;
	}
	delete[] this->hash_table;
}
//Complexity: Theta(n)

