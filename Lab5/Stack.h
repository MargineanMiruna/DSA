#include "SortedSet.h"

class Stack {
private:
    BSTNode **s;
    int cap;
    int nrElems;
    void resize();
public:
    Stack();
    void push(BSTNode *node);
    BSTNode *pop();
    BSTNode *top();
    bool isEmpty();
    void clear();
};
