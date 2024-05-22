#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

//theta(1)
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
    this->index = 0;
    this->occurence = 1;
}

//theta(1)
TComp SortedBagIterator::getCurrent() {
    if(this->valid())
        return this->bag.elements[this->index].first;
    throw exception();
}

//theta(1)
bool SortedBagIterator::valid() {
    if(this->index >= 0 && this->index < this->bag.nrElements && this->occurence <= this->bag.elements[this->index].second)
        return true;
	return false;
}

//theta(1)
void SortedBagIterator::next() {
    if(this->valid())
        if(this->occurence < this->bag.elements[this->index].second)
            this->occurence ++;
        else {
            this->index ++;
            this->occurence = 1;
        }
    else
        throw exception();
}

//theta(1)
void SortedBagIterator::first() {
    this->index = 0;
    this->occurence = 1;
}

