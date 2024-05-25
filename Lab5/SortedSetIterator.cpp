#include "SortedSetIterator.h"
#include <exception>

using namespace std;

//bester Fall: theta(1)
//schlechtester Fall: theta(n), n = multime.nrElems
//durchschnittlicher Fall: theta(n)
//Komplexitat: O(n)
SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	BSTNode *it = multime.root;
    while(it != nullptr) {
        s.push(it);
        it = it->leftChild;
    }
    if(!s.isEmpty())
        index = s.top();
    else index = nullptr;
}

//bester Fall: theta(1)
//schlechtester Fall: theta(n), n = multime.nrElems
//durchschnittlicher Fall: theta(n)
//Komplexitat: O(n)
void SortedSetIterator::first() {
    BSTNode *it = multime.root;
    s.clear();
    while(it != nullptr) {
        s.push(it);
        it = it->leftChild;
    }
    if(!s.isEmpty())
        index = s.top();
    else index = nullptr;
}

//bester Fall: theta(1)
//schlechtester Fall: theta(n), n = multime.nrElems
//durchschnittlicher Fall: theta(n)
//Komplexitat: O(n)
void SortedSetIterator::next() {
    if(index == nullptr)
        throw exception();
	BSTNode *it = s.pop();
    if(it->rightChild != nullptr) {
        it = it->rightChild;
        while(it != nullptr) {
            s.push(it);
            it = it->leftChild;
        }
    }
    if(!s.isEmpty())
        index = s.top();
    else index = nullptr;
}

//theta(1)
TElem SortedSetIterator::getCurrent() {
    if(index == nullptr)
        throw exception();
	return index->value;
}

//theta(1)
bool SortedSetIterator::valid() const {
	return index != nullptr;
}