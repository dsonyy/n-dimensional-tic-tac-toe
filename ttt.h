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


void write(const Map & map);

size_t get_offset_by_dim(size_t dim);

bool is_first_in_dim(size_t pos, size_t dim);
bool is_last_in_dim(size_t pos, size_t dim);

size_t get_first_in_this_dim(size_t pos, size_t dim);
size_t get_last_in_this_dim(size_t pos, size_t dim);

vector<size_t> pos_to_vector(size_t pos);
size_t         vector_to_pos(vector<size_t> v);

Field get_field(const Map & map, vector<size_t> v);
Field get_field(const Map & map, size_t pos);

bool set_field(Map & map, Field field, vector<size_t> v, bool overwrite = false);
bool set_field(Map & map, Field field, size_t pos, bool overwrite = false);

bool check_win(const Map & map, vector<size_t> v);
bool check_win(const Map & map, size_t pos);


#endif
