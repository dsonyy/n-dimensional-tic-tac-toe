#ifndef _TTT_HEADER_
#define _TTT_HEADER_

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;


enum Field
{ 
	EMPTY,
	X, 
	O,
};
typedef vector<Field> Map;




void write(const Map & map, size_t a);

size_t get_offset_by_dim(size_t a, size_t n);

bool is_first_in_dim(size_t pos, size_t a, size_t n);

bool is_last_in_dim(size_t pos, size_t a, size_t n);

vector<size_t> pos_to_vector(size_t pos, size_t a, size_t n);

size_t vector_to_pos(vector<size_t> v, size_t a, size_t n);


#endif
