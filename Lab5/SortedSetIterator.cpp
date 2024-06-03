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

void SortedSetIterator::modifyCurrent(TComp value) {
    BSTNode *it = index, *exist = multime.root, *parentOld = multime.SortedSet::parent(index), *repl = nullptr;
    bool found = false;
    while(!found && exist != nullptr) {
        if(exist->value == value)
            found = true;
        else if(multime.r(value, exist->value)) {
            if(exist->leftChild != nullptr)
                exist = exist->leftChild;
            else exist->leftChild->value = value;
        }
        else {
            if(exist->rightChild != nullptr)
                exist = exist->rightChild;
            else exist->rightChild->value = value;
        }
    }
    if(it->leftChild == nullptr && it->rightChild == nullptr) {
        if (parentOld != nullptr) {
            if (parentOld->leftChild != nullptr && parentOld->leftChild->value == it->value)
                parentOld->leftChild = nullptr;
            else
                parentOld->rightChild = nullptr;
        }
        else multime.root = nullptr;
    }
    else if(it->leftChild != nullptr || it->rightChild != nullptr) {
        while(it->leftChild != nullptr || it->rightChild != nullptr) {
            if(it->leftChild != nullptr)
                repl = multime.maximum(it->leftChild);
            else repl = multime.minimum(it->rightChild);
            parentOld = multime.parent(repl);
            it->value = repl->value;
            it = repl;
        }
        if(parentOld->leftChild == it) parentOld->leftChild = nullptr;
        else parentOld->rightChild = nullptr;
    }
}