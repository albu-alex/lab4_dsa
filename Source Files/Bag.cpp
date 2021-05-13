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
//Complexity: Theta(1)


void Bag::add(TElem elem) {
	if(this->length*1.0/this->capacity*1.0>=0.7){
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
	        //when i add an element the second time, frequency will not be updated
	        current_element->frequency++;
	        this->length++;
	        return;
        }
	    new_element->next = this->hash_table[position].head;
	    this->hash_table[position].head = new_element;
	}
	this->length++;
}
//Complexity: O(length_of_SLL)

void Bag::resize() {
    this->capacity*=2;
    this->divisor = this->capacity;
    Node* current_node;
    int position;
    SLL* resized_hash_table = new SLL[this->capacity];
    for(int i=0;i<this->capacity;i++)
        resized_hash_table[i].head = nullptr;
    for(int i=0;i<this->capacity/2;i++) {
        current_node = this->hash_table[i].head;
        while(current_node!= nullptr){
            position = abs(current_node->element%this->divisor);
            Node* new_element = new Node();
            new_element->frequency = current_node->frequency;
            new_element->element = current_node->element;
            new_element->next = resized_hash_table[position].head;
            resized_hash_table[position].head = new_element;
            current_node = current_node->next;
        }
    }
    this->hash_table = resized_hash_table;
}
//Complexity: O(n*length_of_SLL), where n is former capacity

bool Bag::remove(TElem elem) {
    int position=abs(elem%this->divisor);
    Node* current_element;
    Node* previous_element=nullptr;
    if(this->hash_table[position].head == nullptr)
        return false;
    current_element = this->hash_table[position].head;
    while(current_element != nullptr && current_element->element != elem) {
        previous_element = current_element;
        current_element = current_element->next;
    }
    if(previous_element == nullptr && current_element != this->hash_table[position].head)
        return false;
    if(current_element!= nullptr && current_element->element == elem)
    {
        if(current_element->frequency > 1) {
            current_element->frequency--;
            this->length--;
        }
        else{
            this->length--;
            if(current_element == this->hash_table[position].head){
                this->hash_table[position].head = this->hash_table[position].head->next;
            }
            else {
                previous_element->next = current_element->next;
            }
        }
        return true;
    }
	return false; 
}
//Complexity: O(length_of_SLL)


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
//Complexity: O(length_of_SLL)


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
//Complexity: O(length_of_SLL)


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
//Complexity: Theta(1)

Bag::~Bag() {
	for(int i=0;i<this->capacity;i++){
	    delete this->hash_table[i].head;
	}
	delete[] this->hash_table;
}
//Complexity: Theta(n)

