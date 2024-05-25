#include "SortedSet.h"
#include "SortedSetIterator.h"

//theta(1)
SortedSet::SortedSet(Relation r) {
    this->r = r;
    this->root = nullptr;
    this->nrElems = 0;
}

//bester Fall: theta(1)
//schlechtester Fall: theta(n), n = nrElems
//durchschnittlicher Fall: theta(n)
//Komplexitat: O(n)
BSTNode *SortedSet::minimum(BSTNode *root) {
    BSTNode *it = root;
    while(it->leftChild != nullptr)
        it = it->leftChild;
    return it;
}

//bester Fall: theta(1)
//schlechtester Fall: theta(n), n = nrElems
//durchschnittlicher Fall: theta(n)
//Komplexitat: O(n)
BSTNode *SortedSet::maximum(BSTNode *root) {
    BSTNode *it = root;
    while(it->rightChild != nullptr)
        it = it->rightChild;
    return it;
}

//bester Fall: theta(1)
//schlechtester Fall: theta(n), n = nrElems
//durchschnittlicher Fall: theta(n)
//Komplexitat: O(n)
BSTNode *SortedSet::parent(BSTNode *child) {
    BSTNode *it = root, *parent = nullptr;
    while(it != child) {
        parent = it;
        if(r(child->value, it->value))
            it = it->leftChild;
        else
            it = it->rightChild;
    }
    return parent;
}

//bester Fall: theta(1)
//schlechtester Fall: theta(n), n = nrElems
//durchschnittlicher Fall: theta(n)
//Komplexitat: O(n)
bool SortedSet::add(TComp elem) {
    auto *newNode = new BSTNode;
    newNode->value = elem;
    newNode->leftChild = nullptr;
    newNode->rightChild = nullptr;
    if(nrElems == 0) {
        root = newNode;
    }
    else {
        BSTNode *it = root;
        bool found = false;
        while(!found)
            if(it->value == elem) return false;
            else if(r(elem, it->value)) {
                if(it->leftChild != nullptr)
                    it = it->leftChild;
                else {
                    found = true;
                    it->leftChild = newNode;
                }
            }
            else if(r(it->value, elem)) {
                if(it->rightChild != nullptr)
                    it = it->rightChild;
                else {
                    found = true;
                    it->rightChild = newNode;
                }
            }
    }
    nrElems++;
	return true;
}

//bester Fall: theta(1)
//schlechtester Fall: theta(n), n = nrElems
//durchschnittlicher Fall: theta(n)
//Komplexitat: O(n)
bool SortedSet::remove(TComp elem) {
    BSTNode *it = root, *prnt = nullptr, *repl;
    if(it == nullptr)
        return false;
    while(it->value != elem) {
        prnt = it;
        if (r(elem, it->value)) {
            if (it->leftChild != nullptr)
                it = it->leftChild;
            else return false;
        }
        else if (r(it->value, elem)) {
            if (it->rightChild != nullptr)
                it = it->rightChild;
            else return false;
        }
    }
    if(it->leftChild == nullptr && it->rightChild == nullptr) {
        if (prnt != nullptr) {
            if (prnt->leftChild != nullptr && prnt->leftChild->value == elem)
                prnt->leftChild = nullptr;
            else
                prnt->rightChild = nullptr;
        }
        else root = nullptr;
    }
    else if(it->leftChild != nullptr || it->rightChild != nullptr) {
        while(it->leftChild != nullptr || it->rightChild != nullptr) {
            if(it->leftChild != nullptr)
                repl = maximum(it->leftChild);
            else repl = minimum(it->rightChild);
            prnt = parent(repl);
            it->value = repl->value;
            it = repl;
        }
        if(prnt->leftChild == it) prnt->leftChild = nullptr;
        else prnt->rightChild = nullptr;
    }
    nrElems--;
    return true;
}

//bester Fall: theta(1)
//schlechtester Fall: theta(n), n = nrElems
//durchschnittlicher Fall: theta(n)
//Komplexitat: O(n)
bool SortedSet::search(TComp elem) const {
    BSTNode *it = root;
    if(it == nullptr)
        return false;
    while(it->value != elem) {
        if (r(elem, it->value)) {
            if (it->leftChild != nullptr)
                it = it->leftChild;
            else return false;
        }
        else if (r(it->value, elem)) {
            if (it->rightChild != nullptr)
                it = it->rightChild;
            else return false;
        }
    }
	return true;
}

//theta(1)
int SortedSet::size() const {
	return nrElems;
}

//theta(1)
bool SortedSet::isEmpty() const {
	return nrElems == 0;
}

//theta(1)
SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}

//theta(n), n = nrElems
SortedSet::~SortedSet() {
    SortedSetIterator it(*this);
    BSTNode *current;
    while(it.valid()) {
        current = it.index;
        it.next();
        delete current;
    }
	root = nullptr;
}
