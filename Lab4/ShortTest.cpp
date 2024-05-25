#include <assert.h>
#include "Matrix.h"

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);

    m.modify(1, 4, 9);
    m.modify(2,3, 7);
    m.modify(2, 4, 23);
    m.modify(2, 2, 18);
    m.modify(3, 1, 12);
    m.modify(3, 2, 5);
    m.modify(3, 4, 75);
    m.modify(4, 2, 7);
    m.modify(4, 4, 12);

    //6 0 0 9
    //0 18 7 23
    //12 5 0 75
    //0 7 0 12

    assert(m.position(9).first == 1);
    assert(m.position(9).second == 4);
    assert(m.position(7).first == 2);
    assert(m.position(7).second == 3);
    assert(m.position(75).first == 3);
    assert(m.position(75).second == 4);
}