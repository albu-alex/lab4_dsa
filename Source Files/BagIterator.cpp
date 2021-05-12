#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->hash_table = this->bag.hash_table;
    this->current_position=0;
    this->frequency=1;
	while(this->current_position < this->bag.capacity && this->hash_table[this->current_position].head == nullptr) this->current_position++;
	if(this->current_position == this->bag.capacity) this->current_node = nullptr;
	else this->current_node = this->bag.hash_table[this->current_position].head;
}
//Complexity: O(length_of_hashtable)

void BagIterator::first() {
    this->current_position=0;
    this->frequency=1;
    while(this->current_position < this->bag.capacity && this->hash_table[this->current_position].head == nullptr) this->current_position++;
    if(this->current_position == this->bag.capacity) this->current_node = nullptr;
    else this->current_node = this->bag.hash_table[this->current_position].head;
}
//Complexity: O(length_of_hashtable)


void BagIterator::next(){
    if(!valid())
        throw exception();
    if(this->frequency == this->current_node->frequency){
        this->current_node = this->current_node->next;
        if(this->current_node == nullptr && this->current_position < this->bag.capacity-1){
            this->current_position++;
            while(this->bag.hash_table[this->current_position].head == nullptr && this->current_position < this->bag.capacity-1) this->current_position++;
            this->current_node = this->bag.hash_table[current_position].head;
            this->frequency=1;
        }
    }
    else{
        this->frequency++;
    }
}
//Complexity: O(length_of_hashtable)


bool BagIterator::valid() const {
	if(this->current_node == nullptr)
	    return false;
	return true;
}
//Theta(1)


TElem BagIterator::getCurrent() const
{
    if(valid())
        return this->current_node->element;
    else
        throw exception();
}
//Theta(1)
