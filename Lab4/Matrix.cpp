#include "Matrix.h"
#include <exception>
using namespace std;

//theta(n), n = m
Matrix::Matrix(int nrLines, int nrCols) {
    lines = nrLines;
    cols = nrCols;
    m = 10;
    elems = new Element[m];
    next = new int[m];
    firstEmpty = 0;
    for(int i = 0; i < m; i++){
        elems[i].value = -1;
        elems[i].i = -1;
        elems[i].j = -1;
        next[i] = -1;
    }
}

//theta(1)
int Matrix::nrLines() const {
	return lines;
}

//theta(1)
int Matrix::nrColumns() const {
	return cols;
}

//theta(1)
int Matrix::hash(int i, int j) const {
    return (i + j) % m;
}

//bester Fall: theta(1)
//schlechtester Fall: theta(n), n = m
//durchschnittlicher Fall: theta(n), n = m
//Komplexitat: O(n)
int Matrix::nextEmpty(Element *el) const {
    int nextEmpty = firstEmpty + 1;
    while(nextEmpty < m && el[nextEmpty].value != -1)
        nextEmpty++;
    return nextEmpty;
}

//bester Fall: theta(n), n = m
//schlechtester Fall: theta(n*p), n = oldCap, p = Anzahl der Elementen
//durchschnittlicher Fall: theta(n*p)
//Komplexitat: O(n*p)
void Matrix::resize() {
    int oldCap = m;
    m *= 2;
    int pos;
    auto *newElems = new Element[m];
    int *newNext = new int[m];
    firstEmpty = 0;
    for(int i = 0; i < m; i++){
        newElems[i].value = -1;
        newElems[i].i = -1;
        newElems[i].j = -1;
        newNext[i] = -1;
    }
    for(int i = 0; i < oldCap; i++) {
        pos = hash(elems[i].i, elems[i].j);
        if(newElems[pos].value != -1) {
            while(newNext[pos] != -1)
                pos = newNext[pos];
            newNext[pos] = firstEmpty;
            pos = firstEmpty;
            firstEmpty = nextEmpty(newElems);
        }
        else if(pos == firstEmpty)
            firstEmpty = nextEmpty(newElems);
        newElems[pos].i = elems[i].i;
        newElems[pos].j = elems[i].j;
        newElems[pos].value = elems[i].value;
    }
    delete[] elems;
    elems = newElems;
    delete[] next;
    next = newNext;
}

//bester Fall: theta(1)
//schlechtester Fall: theta(n), n = Anzahl der Elemente
//durchschnittlicher Fall: theta(1)
//Komplexitat: O(n)
TElem Matrix::element(int i, int j) const {
    if(i < 0 || i > lines || j < 0 || j > cols)
        throw exception();
    int pos = hash(i, j);
    if(elems[pos].i == i && elems[pos].j == j)
        return elems[pos].value;
    pos = next[pos];
    while(pos != -1){
        if(elems[pos].i == i && elems[pos].j == j)
            return elems[pos].value;
        pos = next[pos];
    }
    return NULL_TELEM;
}

//bester Fall: theta(1) - findet das Element auf der ersten Position und andert sie
//schlechtester Fall: theta(n+p), n = m, p = Anzahl der Elementen - alle Elemente sind auf derselben Position gehasht und wir mochten den letzten loschen
//durchschnittlicher Fall: theta(n+p)
//Komplexitat: O(n+p)
TElem Matrix::modify(int i, int j, TElem e) {
    if(i < 0 || i > lines || j < 0 || j > cols)
        throw exception();
    if(firstEmpty == m)
        resize();
    int pos = hash(i, j);
    int oldValue = -1, prev = -1, nxt, aux = 0;

    if(elems[pos].i == i && elems[pos].j == j)//wenn Element sich auf gehashter Position befindet
        oldValue = elems[pos].value;
    while(next[pos] != -1 && oldValue == -1) { //sucht auf den nachsten Positionen
        pos = next[pos];
        if(elems[pos].i == i && elems[pos].j == j)
            oldValue = elems[pos].value;
    }

    if(e != 0 && oldValue != -1) {//update
        elems[pos].value = e;
    }
    else if(e != 0 && oldValue == -1) {//add
        if(elems[pos].value != -1) {
            next[pos] = firstEmpty;
            pos = firstEmpty;
            firstEmpty = nextEmpty(elems);
        }
        else if(pos == firstEmpty)
            firstEmpty = nextEmpty(elems);
        elems[pos].i = i;
        elems[pos].j = j;
        elems[pos].value = e;
    }
    else if(e == 0 && oldValue != -1) {//delete
        nxt = next[pos];
        while(aux < m && prev == -1) {
            if(next[aux] == pos)
                prev = aux;
            aux++;
        }
        if(prev != -1)
            next[prev] = nxt;
        while(nxt != -1) {
            if(hash(elems[nxt].i, elems[nxt].j) == pos) {
                if(prev != -1) next[prev] = pos;
                elems[pos].i = elems[nxt].i;
                elems[pos].j = elems[nxt].j;
                elems[pos].value = elems[nxt].value;
                next[pos] = next[nxt];
                pos = nxt;
            }
            if(prev != -1) prev = next[prev];
            else prev = nxt;
            nxt = next[nxt];
        }
        elems[pos].value = -1;
        elems[pos].i = -1;
        elems[pos].j = -1;
        next[pos] = -1;
        if(pos < firstEmpty)
            firstEmpty = pos;
    }
    if(oldValue != -1)
        return oldValue;
    return NULL_TELEM;
}

//theta(1)
Matrix::~Matrix() {
	delete[] elems;
    delete[] next;
}

//bester Fall: theta(1)
//schlechtester Fall: theta(n), n = m
//durchschnittlicher Fall: theta(n), n = m
//Komplexitat: O(n)
std::pair<int, int> Matrix::position(TElem elem) {//n am tratat cazul in care elem = 0
    for(int i = 0; i < m; i++)
        if(elems[i].value == elem)
            return make_pair(elems[i].i, elems[i].j);
    return make_pair(-1, -1);
}
