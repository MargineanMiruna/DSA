#pragma once
#include "SortedSet.h"
#include "Stack.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& multime;
	SortedSetIterator(const SortedSet& m);

    Stack s;
    BSTNode *index;
public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};

