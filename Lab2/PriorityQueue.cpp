
#include "PriorityQueue.h"
#include <exception>
using namespace std;

//theta(1)
PriorityQueue::PriorityQueue(Relation r) {
	//TODO - Implementation
    this->r = r;
    this->head = nullptr;
    this->tail = nullptr;
    this->nrElements = 0;
}

//bester Fall: theta(1)
//schlechtester Fall: theta(nrElements)
//durchschnittlicher Fall: theta(nrElements)
//allgemeine Komplexitat: O(nrElements)
void PriorityQueue::push(TElem e, TPriority p) {
	//TODO - Implementation
    DLLNode *newNode = new DLLNode;
    DLLNode *it;
    newNode->info = make_pair(e, p);
    if(this->head == nullptr) {
        newNode->next = nullptr;
        newNode->prev = nullptr;
        this->head = newNode;
        this->tail = this->head;
    }
    else if(this->r(p, this->head->info.second)) {
        newNode->prev = nullptr;
        this->head->prev = newNode;
        newNode->next = this->head;
        this->head = newNode;
    }
    else if(this->r(this->tail->info.second, p)) {
        newNode->next = nullptr;
        this->tail->next = newNode;
        newNode->prev = this->tail;
        this->tail = newNode;
    }
    else {
        it = this->head;
        while(!this->r(p, it->info.second))
            it = it->next;
        it->prev->next = newNode;
        newNode->prev = it->prev;
        newNode->next = it;
        it->prev = newNode;
    }
    this->nrElements++;
}

//theta(1)
//throws exception if the queue is empty
Element PriorityQueue::top() const {
	//TODO - Implementation
    if(this->nrElements == 0)
        throw exception();
	return this->head->info;
}

//theta(1)
Element PriorityQueue::pop() {
	//TODO - Implementation
    if(this->nrElements == 0)
        throw exception();
    Element value;
    value = this->head->info;
    if(this->head->next == nullptr) {
        delete this->head;
        this->head = nullptr;
        this->tail = nullptr;
    }
    else {
        this->head = this->head->next;
        delete this->head->prev;
    }
    this->nrElements--;
    return value;
}

//theta(1)
bool PriorityQueue::isEmpty() const {
	//TODO - Implementation
	return this->nrElements == 0;
}

//theta(nrElements)
PriorityQueue::~PriorityQueue() {
	//TODO - Implementation
    DLLNode *it = this->head;
    DLLNode *currrent;
    while(it != nullptr) {
        currrent = it;
        it = it->next;
        delete currrent;
    }
    this->head = nullptr;
    this->tail = nullptr;
};

//theta(this->nrElements + other.nrElements)
PriorityQueue PriorityQueue::interclasare(PriorityQueue other) {
    PriorityQueue newQueue(this->r);
    DLLNode *i, *j;
    i = this->head;
    j = other.head;
    if(this->r(this->head->info.second, other.head->info.second)){
        newQueue.head = this->head;
        i = i->next;
    }
    else {
        newQueue.head = other.head;
        j = j->next;
    }
    newQueue.tail = newQueue.head;
    newQueue.head->next = nullptr;
    newQueue.tail->next = nullptr;
    while(i != nullptr && j != nullptr){
        if(this->r(i->info.second, j->info.second)){
            newQueue.tail->next = i;
            i = i->next;
        }
        else {
            newQueue.tail->next = j;
            j = j->next;
        }
        newQueue.tail->next->prev = newQueue.tail;
        newQueue.tail = newQueue.tail->next;
        newQueue.tail->next = nullptr;
    }
    while(i != nullptr){
        newQueue.tail->next = i;
        i = i->next;
        newQueue.tail->next->prev = newQueue.tail;
        newQueue.tail = newQueue.tail->next;
        newQueue.tail->next = nullptr;
    }
    while(j != nullptr){
        newQueue.tail->next = j;
        j = j->next;
        newQueue.tail->next->prev = newQueue.tail;
        newQueue.tail = newQueue.tail->next;
        newQueue.tail->next = nullptr;
    }
    return newQueue;
}
//interclasare(pq, pq1)
//descr: erstellt eine neue Prioritatsschlange mit den Elementen der Prioritatsschlangen pq und pq1
//mit den Elementen sorteiert nach Prioritat
//pre: pq, pq1 zwei Prioritatsschlangen
//post: pq2 eine Prioritatschlange mit den elementen von pq und pq2 sortiert

//algorithm interclasare(pq, pq1)
// newQueue.head <- head with the best priority between pq.head, pq1.head
// i <- pq.head
// j <- pq1.head
// while i != NIL and Jj != NIL do
//    if i has best priority between i and j
//       newQueue.tail <- i
//       i <- i.next
//    else
//       newQueue.tail <- j
//       j <- j.next
// while i != NIL do
//    newQueue.tail <- i
//    i <- i.next
// while j != NIL do
//    newQueue.tail <- j
//    j <- j.next
//returns newQueue