#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <algorithm>
#include <utility>

//theta(1)
SortedBag::SortedBag(Relation r) {
    this->r = r;
    this->capacity = 10;
    this->nrElements = 0;
    this->elements = new std::pair<TComp, int> [this->capacity];
}

//theta(this->capacity)
void SortedBag::resize_up() {
    int new_capacity = this->capacity * 2;
    auto *resized = new std::pair<TComp, int> [new_capacity];
    for(int i = 0; i < this->capacity; i++)
        resized[i] = this->elements[i];
    this->capacity = new_capacity;
    delete[] this->elements;
    this->elements = resized;
}

//theta(this->nrElements)
void SortedBag::resize_down() {
    int new_capacity = this->capacity / 2;
    auto *resized = new std::pair<TComp, int> [new_capacity];
    for(int i = 0; i < this->nrElements; i++)
        resized[i] = this->elements[i];
    this->capacity = new_capacity;
    delete[] this->elements;
    this->elements = resized;
}

//bester Fall: theta(1)
//schlechtester Fall: theta(this->nrElements)
//durchschnittlicher Fall: theta(this->nrElements)
//allgemeine Komplexitat: O(this->nrElements)
void SortedBag::add(TComp e) {
    if(this->nrElements == this->capacity)
       this->resize_up();
    if(this->nrElements == 0) {
       this->elements[0] = std::make_pair(e, 1);
       this->nrElements ++;
    }
    else if(this->r(e, this->elements[this->nrElements - 1].first)){
        int i = 0;
        while(!this->r(e, this->elements[i].first) && i < this->nrElements)
            i++;
        if(this->elements[i].first == e)
            this->elements[i].second ++;
        else {
            for(int j = this->nrElements; j > i; j--)
                this->elements[j] = this->elements[j - 1];
            this->elements[i] = std::make_pair(e, 1);
            this->nrElements++;
        }
    }
    else {
        this->elements[this->nrElements] = std::make_pair(e, 1);
        this->nrElements++;
    }
}

//bester Fall: theta(log2(this->nrElements))
//schlechtester Fall: theta(this->nrElements)
//durchschnittlicher Fall: theta(this->nrElements)
//allgemeine Komplexitat: O(this->nrElements)
bool SortedBag::remove(TComp e) {
    if(this->nrElements < this->capacity / 4 && !this->isEmpty())
        this->resize_down();
    if(this->search(e)){
        for(int i = 0; i < this->nrElements; i++){
            if(this->elements[i].first == e){
                if(this->elements[i].second > 1) {
                    this->elements[i].second --;
                    return true;
                }
                else {
                    for (int j = i; j < this->nrElements - 1; j++)
                        this->elements[j] = this->elements[j + 1];
                    this->nrElements --;
                    return true;
                }
            }
        }
    }
    return false;
}

//bester Fall: theta(1)
//schlechtester Fall: theta(log2(this->nrElements))
//durchschnittlicher Fall: theta(log2(this->nrElements))
//allgemeine Komplexitat: O(log2(this->nrElements))
bool SortedBag::search(TComp elem) const {
    int left = 0;
    int right = this->nrElements - 1;
    int poz = -1, m;
    while(left <= right && poz == -1){
        m = (left + right) / 2;
        if(this->elements[m].first == elem)
            poz = m;
        else{
            if(this->r(this->elements[m].first, elem))
                left = m + 1;
            else
                right = m - 1;
        }
    }
    if(poz != -1)
        return true;
	return false;
}

//bester Fall: theta(1)
//schlechtester Fall: theta(log2(this->nrElements))
//durchschnittlicher Fall: theta(log2(this->nrElements))
//allgemeine Komplexitat: O(log2(this->nrElements))
int SortedBag::nrOccurrences(TComp elem) const {
    int left = 0;
    int right = this->nrElements - 1;
    int poz = -1, m;
    while(left <= right && poz == -1){
        m = (left + right) / 2;
        if(this->elements[m].first == elem)
            poz = m;
        else{
            if(this->r(this->elements[m].first, elem))
                left = m + 1;
            else
                right = m - 1;
        }
    }
    if(poz == -1)
        return 0;
    return this->elements[poz].second;
}

//theta(this->nrElements)
int SortedBag::size() const {
    int s = 0;
    for(int i = 0; i < this->nrElements; i++)
        s += this->elements[i].second;
	return s;
}

//theta(1)
bool SortedBag::isEmpty() const {
    if(this->nrElements == 0)
        return true;
	return false;
}

//theta(1)
SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}

//bester Fall: theta(this->nrElements)
//schlechtester Fall: theta(this->nrElements)
//durchschnittlicher Fall: theta(this->nrElements)
//allgemeine Komplexitat: theta(this->nrElements)
TComp SortedBag::removeFreqElement() {
    int maxi = -1, idx, e;
    for(int i = 0; i < this->nrElements; i++)
        if(this->elements[i].second > maxi) {
            maxi = this->elements[i].second;
            idx = i;
            e = this->elements[i].first;
        }//search most frequent element
    if(this->nrElements < this->capacity / 4 && !this->isEmpty())
        this->resize_down();
    for(int i = idx; i < this->nrElements - 1; i++)
        this->elements[i] = this->elements[i + 1];//Verschieben
    this->nrElements --;
    return e;
}

//Domane: SB = {sb|sb ist ein SortedBag von Typ Paaren von Element TComp und Frequenz int}
//removeFreqElement(sb)
//descr: loscht alle Vorkommen des Elementes mit den meisten Vorkommen
//pre: sb - SB
//post: sb' - SB, sb' = sb \ {el| el hat die meisten Vorkommen} alle Vorkommen des Elementes mit den meisten
//Vorkommen wurden entfernt
//removeFreqElement <- el

//maxi <- -1
//for i <- 0, nr of elements do
//   if frequency of element on position i > maxi then
//      maxi <- frequency of the element on position i
//      idx <- position i
//      e <- value of element on position i
//if needed resize then
//   resize()
//for i <- idx, nr of elements do
//   element on position i becomes element on position i+1
//nr of elements = nr of elements - 1
//return e

//theta(1)
SortedBag::~SortedBag() {
    delete[] this->elements;
}
