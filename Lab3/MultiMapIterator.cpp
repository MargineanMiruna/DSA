#include "MultiMapIterator.h"
#include "MultiMap.h"

//complexity theta(1)
MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    current = col.head;
    values_iterator = col.elems[col.head].second.head;
}

//complexity theta(1)
TElem MultiMapIterator::getCurrent() const{
    if(current == -1)
        throw exception();
    return col.elems[current].second.elems[values_iterator];
}

//complexity theta(1)
bool MultiMapIterator::valid() const {
    return current != -1;
}

//complexity theta(1)
void MultiMapIterator::next() {
    if(current == -1)
        throw exception();
    if(col.elems[current].second.next[values_iterator] != -1)
        values_iterator = col.elems[current].second.next[values_iterator];
    else {
        current = col.next[current];
        values_iterator = col.elems[current].second.head;
    }
}

//complexity theta(1)
void MultiMapIterator::first() {
    current = col.head;
    values_iterator = col.elems[current].second.head;
}

