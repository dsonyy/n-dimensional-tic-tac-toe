#include "ttt.h"
#include <iostream>
#include <vector>
#include <functional>
#include <cstdlib>
#include <cmath>

using namespace std;


int map_length(size_t n, size_t a)
{
	return pow(a, n);
}

int get_offset_by_dim(size_t dim, size_t a)
{
	return pow(a, dim - 1);
}

bool is_first_in_dim(MapPos pos, size_t dim, size_t a)
{
	return pos % int(pow(a, dim)) < pow(a, dim-1);
}

bool is_last_in_dim(MapPos pos, size_t dim, size_t a)
{
	return pos % int(pow(a, dim)) >= (a - 1) * pow(a, dim - 1);
}

VMapPos pos_to_vector(MapPos pos, size_t n, size_t a)
{
	if (pos < 0 || pos >= pow(a, n))
	{
		return VMapPos();
	}
	
	VMapPos new_vpos(n);
	size_t N = n;

	while (N > 0)
	{
		new_vpos[N - 1] = pos / size_t(pow(a, N - 1));
		pos %= size_t(pow(a, N - 1));
		N--;
	}

	return new_vpos;
}

MapPos vector_to_pos(VMapPos vpos, size_t n, size_t a)
{
	size_t new_pos = 0;

	for (int i = 0; i < (vpos.size() > n ? n : vpos.size()); i++)
	{
		new_pos += vpos[i] * size_t(pow(a, i));
	}

	return new_pos;
}

Field get_field(const Map & map, MapPos pos)
{
	return map[pos];
}

bool set_field(Map & map, Field field, MapPos pos, size_t n, size_t a, bool overwrite)
{
	if (pos < 0)
	{
		return false;
	}

	if (!overwrite && map[pos] != EMPTY)
	{
		return false;
	}

	if (pos >= pow(a, n))
	{
		return false;
	}

	map[pos] = field;
	return true;
}

Field check_win(const Map & map, MapPos pos, 
	size_t n, size_t a, size_t r, vector<VMapPos> neighbours_offsets)
{
	int lines_count = 0;

	for (auto offset : neighbours_offsets)
	{
		if (check_line(map, pos, offset, n, a, r))
		{
			lines_count++;
		}
	}

	if (lines_count == 0)
	{
		return EMPTY;
	}
	else
	{
		return map[pos];
	}
}

vector<VMapPos> get_neighbours_offsets(size_t n, size_t a)
{
	vector<VMapPos> offsets;

	function<void(size_t dim, VMapPos offset)> checker;
	checker = [&](size_t dim, VMapPos offset)
	{
		for (int i : {-1, 0, 1})
		{
			offset[dim - 1] = i;
			if (dim > 1)
			{
				checker(dim - 1, offset);
			}
			else if (dim == 1 && vector_to_pos(offset, n, a) > 0)
			{
				offsets.push_back(offset);
			}
		}
	};
	
	checker(n, VMapPos(n, 0));
	return offsets;
}

bool valid_vectors_addition(VMapPos pos, VMapPos offset, size_t n, size_t a)
{
	for (auto i = 0; i < n; i++)
	{
		if (pos[i] + offset[i] < 0 || pos[i] + offset[i] >= a)
		{
			return false;
		}
	}

	return true;
}

bool valid_vectors_subtraction(VMapPos pos, VMapPos offset, size_t n, size_t a)
{
	for (auto i = 0; i < n; i++)
	{
		if (pos[i] - offset[i] < 0 || pos[i] - offset[i] >= a)
		{
			return false;
		}
	}

	return true;
}


bool check(VMapPos pos, VMapPos offset, bool neg, size_t n, size_t a)
{
	for (auto i = 0; i < n; i++)
	{
		if (!neg)
		{
			if (pos[i] + offset[i] < 0 || pos[i] + offset[i] >= a)
			{
				return false;
			}
		}
		else
		{
			if (pos[i] - offset[i] < 0 || pos[i] - offset[i] >= a)
			{
				return false;
			}
		}
	}

	return true;
}

bool check_line(const Map & map, MapPos pos, VMapPos offset, size_t n, size_t a, size_t r)
{
	if (map[pos] == EMPTY) return false;

	Field field = map[pos];
	int count = 1;
	int i = pos;

	while (valid_vectors_addition(pos_to_vector(i, n, a), offset, n, a) && 
		map[i + vector_to_pos(offset, n, a)] == field)
	{
		count++;
		i += vector_to_pos(offset, n, a);
	}
	
	i = pos;

	while (valid_vectors_subtraction(pos_to_vector(i, n, a), offset, n, a) &&
		map[i - vector_to_pos(offset, n, a)] == field)
	{
		count++;
		i -= vector_to_pos(offset, n, a);
	}

	if (count >= r) return true;

	return false;
}
