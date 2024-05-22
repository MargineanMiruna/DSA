#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

//complexity theta(n), n = cap
MultiMap::MultiMap() {
    cap = 10;
    nrElements = 0;
    head = -1;
    elems = new std::pair<TKey, SLLAValues>[cap];
    next = new int[cap];
    for(int i = 0; i < cap - 1; i++){
        next[i] = i + 1;
    }
    firstEmpty = 0;
    next[cap - 1] = -1;
}

//complexity theta(n), n = elems[i].second.cap
void MultiMap::initValues(int i) {
    elems[i].second.cap = 10;
    elems[i].second.firstEmpty = 0;
    elems[i].second.head = -1;
    elems[i].second.elems = new TElem [elems[i].second.cap];
    elems[i].second.next = new int[elems[i].second.cap];
    for(int j = 0; j < elems[i].second.cap - 1; j++){
        elems[i].second.next[j] = j + 1;
    }
    elems[i].second.next[elems[i].second.cap - 1] = -1;
}

//complexity theta(n), n = cap
void MultiMap::resizeKeys() {
    int newCap = cap * 2;
    auto *newElems = new std::pair<TKey, SLLAValues>[newCap];
    int *newNext = new int[newCap];
    for(int i = 0; i < cap; i++) {
        newElems[i] = elems[i];
        newNext[i] = next[i];
    }
    for(int j = cap; j < newCap - 1; j++){
        newNext[j] = j + 1;
    }
    newNext[newCap - 1] = -1;
    delete[] elems;
    delete[] next;
    elems = newElems;
    next = newNext;
    firstEmpty = cap;
    cap = newCap;
}

//complexity theta(n), n = elems[i].second.cap
void MultiMap::resizeValues(int i) {
    int newCap = elems[i].second.cap * 2;
    auto *newElems = new TElem[newCap];
    int *newNext = new int[newCap];
    for(int j = 0; j < elems[i].second.cap; j++) {
        newElems[j] = elems[i].second.elems[j];
        newNext[j] = elems[i].second.next[j];
    }
    for(int j = elems[i].second.cap; j < newCap - 1; j++){
        newNext[j] = j + 1;
    }
    newNext[newCap - 1] = -1;
    delete[] elems[i].second.elems;
    delete[] elems[i].second.next;
    elems[i].second.elems = newElems;
    elems[i].second.next = newNext;
    elems[i].second.firstEmpty = elems[i].second.cap;
    elems[i].second.cap = newCap;
}

//complexity best case theta(1) the key is found on the first position & key has only one value
//           worst case theta(n+m) - n= cap, m= elems[i].second.cap both arrays are full
//           average case = worst case
//           general case O(n+m)
void MultiMap::add(TKey c, TValue v) {
    if(firstEmpty == -1) // resize if no space available
        resizeKeys();
    if(nrElements == 0) {// add on first position if map is empty
        initValues(firstEmpty);
        elems[firstEmpty].first = c;
        head = firstEmpty;
        firstEmpty = next[firstEmpty];
        next[head] = -1;
        elems[head].second.elems[elems[head].second.firstEmpty] = make_pair(c, v);
        elems[head].second.head = elems[head].second.firstEmpty;
        elems[head].second.firstEmpty = elems[head].second.next[elems[head].second.firstEmpty];
        elems[head].second.next[elems[head].second.head] = -1;
    }
    else {
        int i = head;
        while(i != -1 && elems[i].first != c)
            i = next[i];
        if(i == -1) {//if key doesn't exist
            int j = firstEmpty;
            initValues(j);
            int k = elems[j].second.firstEmpty;
            i = head;
            while(next[i] != -1)
                i = next[i];
            next[i] = j;
            elems[j].first = c;
            firstEmpty = next[firstEmpty];
            next[j] = -1;
            elems[j].second.elems[k] = make_pair(c, v);
            elems[j].second.head = k;
            elems[j].second.firstEmpty = elems[j].second.next[k];
            elems[j].second.next[elems[j].second.head] = -1;
        }
        else if(elems[i].first == c) {//if key already exists
            if (elems[i].second.firstEmpty == -1)
                resizeValues(i);
            int j = elems[i].second.head;
            int k = elems[i].second.firstEmpty;
            while (elems[i].second.next[j] != -1)
                j = elems[i].second.next[j];
            elems[i].second.next[j] = k;
            elems[i].second.elems[k] = make_pair(c, v);
            elems[i].second.firstEmpty = elems[i].second.next[k];
            elems[i].second.next[k] = -1;
        }
    }
    nrElements++;
}

//complexity best case theta(1) key found on the first position and value found on the first position
//           worst case theta(n+m) n=nr of keys, m=nr of values the key has
//           when key found on the last position && ( value found on the last position || value does not exist)
//           average case = worst case
//           general case O(n+m)
bool MultiMap::remove(TKey c, TValue v) {
    int i = head;
    while(i != -1 && elems[i].first != c)
        i = next[i];//searches the key c in the array of keys
    if(i == -1)
        return false;//key not found
    else {//key found
        int j = elems[i].second.head;
        while(j != -1 && elems[i].second.elems[j].second != v)
            j = elems[i].second.next[j];//search the value
        if(j == -1)
            return false;//value not found
        else if(j == elems[i].second.head) {//value found on the first position
            if(elems[i].second.next[j] == -1) {//only one value left
                if(i == head) {//if key is head or if there is only one key left
                    head = next[head];
                }
                else {//key is on a random position
                    int k = head;
                    while(next[k] != i)
                        k = next[k];
                    next[k] = next[i];
                }
                next[i] = firstEmpty;
                firstEmpty = i;
            }
            else {//value is the head of the value list but not the only value left
                elems[i].second.head = elems[i].second.next[j];
                elems[i].second.next[j] = elems[i].second.firstEmpty;
                elems[i].second.firstEmpty = j;
            }
        }
        else {//value is on a random position in the value list
            int k = elems[i].second.head;
            while(elems[i].second.next[k] != j)
                k = elems[i].second.next[k];
            elems[i].second.next[k] = elems[i].second.next[j];
            elems[i].second.next[j] = elems[i].second.firstEmpty;
            elems[i].second.firstEmpty = j;
        }
    }
    nrElements--;
    return true;
}

//complexity best case: theta(1) - if key is on first position and has only one value
//           worst case: theta(n+m) n = nr of keys m = nr of values the key has - if key is on last position and has m values
//           average case = worst case
//           general case: O(n+m)
vector<TValue> MultiMap::search(TKey c) const {
    vector<TValue> values;
    int i = head;
    while(i != -1 && elems[i].first != c)
        i = next[i];//searches the key c in the array of keys
    if(i != -1) {
        int j = elems[i].second.head;//iterate through value list
        while(j != -1) {
            values.push_back(elems[i].second.elems[j].second);//add all values of the key to the vector
            j = elems[i].second.next[j];
        }
    }
    return values;
}

//complexity theta(1)
int MultiMap::size() const {
    return nrElements;
}

//complexity theta(1)
bool MultiMap::isEmpty() const {
    return nrElements == 0;
}

//complexity theta(1)
MultiMapIterator MultiMap::iterator() const {
    return MultiMapIterator(*this);
}

//complexity theta(n) , n = cap
MultiMap::~MultiMap() {
    for(int i = 0; i < cap; i++) {
        delete[] elems[i].second.elems;
        delete[] elems[i].second.next;
    }
    delete[] elems;
    delete[] next;
}

void MultiMap::reverse() {
    int *prev = new int[cap];
    int i = head;
    prev[head] = -1;
    while(next[i] != -1) {
        prev[next[i]] = i;
        i = next[i];
    }
    head = i;
    i = head;
    next = prev;
    while(i != -1){
        reverseValues(i);
        i = next[i];
    }
}

MultiMap::MultiMap(MultiMap &other) {
    elems = other.elems;
    next = other.next;
    head = other.head;
    firstEmpty = other.firstEmpty;
    cap = other.cap;
}


void MultiMap::reverseValues(int i) {
    int *prev = new int[cap];
    int j = elems[i].second.head;
    prev[j] = -1;
    while(elems[i].second.next[j] != -1) {
        prev[elems[i].second.next[j]] = j;
        j = elems[i].second.next[j];
    }
    elems[i].second.head = j;
    elems[i].second.next = prev;
}

