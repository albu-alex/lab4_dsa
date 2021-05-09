#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->current_position=0;
	while(this->bag.hash_table[this->current_position].head == nullptr) this->current_position++;
	this->current_node = this->bag.hash_table[this->current_position].head;
}

void BagIterator::first() {
    this->current_position=0;
    while(this->bag.hash_table[this->current_position].head == nullptr) this->current_position++;
    this->current_node = this->bag.hash_table[this->current_position].head;
}


void BagIterator::next(){
    if(!valid())
        throw exception();
    if(this->current_node != nullptr)
        this->current_node = this->current_node->next;
    else{
        while(this->bag.hash_table[this->current_position].head == nullptr) this->current_position++;
        this->current_node = bag.hash_table[current_position].head;
    }
}


bool BagIterator::valid() const {
	if(this->current_node == nullptr && this->current_position == this->bag.length-1)
	    return false;
	return true;
}



TElem BagIterator::getCurrent() const
{
    return this->current_node->element;
}
