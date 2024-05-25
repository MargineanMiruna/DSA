#include "Stack.h"

//theta(1)
Stack::Stack() {
    cap = 10;
    s = new BSTNode *[cap];
    nrElems = 0;
}

//theta(1)amortisiert
void Stack::push(BSTNode *node) {
    if(nrElems == cap)
        resize();
    s[nrElems] = node;
    nrElems++;
}

//theta(1)
BSTNode *Stack::pop() {
    nrElems--;
    return s[nrElems];
}

//theta(n), n = cap
void Stack::resize() {
    int newCap = cap*2;
    auto newStack = new BSTNode *[newCap];
    for(int i = 0; i < cap; i++)
        newStack[i] = s[i];
    cap = newCap;
    delete[] s;
    s = newStack;
}

//theta(1)
BSTNode *Stack::top() {
    return s[nrElems - 1];
}

//theta(1)
bool Stack::isEmpty() {
    return nrElems == 0;
}

//theta(1)
void Stack::clear() {
    nrElems = 0;
}
