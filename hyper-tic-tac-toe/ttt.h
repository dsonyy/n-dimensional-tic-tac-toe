#ifndef _TTT_HEADER_
#define _TTT_HEADER_

#include <iostream>
#include <vector>
#include <functional>
#include <cstdlib>
using namespace std;

enum Field : char
{ 
	EMPTY = -1,
	O, 
	X,
	Z,
	Y,
	MAX_PLAYERS
};

typedef vector<Field> Map; 
typedef int MapPos;
typedef vector<int> VMapPos;

int map_length(size_t n, size_t a);

int get_offset_by_dim(size_t dim, size_t a);

bool is_first_in_dim(MapPos pos, size_t dim, size_t a);
bool is_last_in_dim(MapPos pos, size_t dim, size_t a);

VMapPos pos_to_vector(MapPos pos, size_t n, size_t a);
MapPos  vector_to_pos(VMapPos vpos, size_t n, size_t a);

Field get_field(const Map & map, MapPos pos);
bool set_field(Map & map, Field field, MapPos pos, size_t n, size_t a, bool overwrite = false);

vector<VMapPos> get_neighbours_offsets(size_t n, size_t a);

Field check_win(const Map & map, MapPos pos,
	size_t n, size_t a, size_t r, vector<VMapPos> neighbours_offsets);
bool check_line(const Map & map, MapPos pos, VMapPos offset, size_t n, size_t a, size_t r);
bool check(VMapPos pos, VMapPos offset, bool neg, size_t n, size_t a);

bool valid_vectors_addition(VMapPos pos, VMapPos offset, size_t n, size_t a);
bool valid_vectors_subtraction(VMapPos pos, VMapPos offset, size_t n, size_t a);


#endif
