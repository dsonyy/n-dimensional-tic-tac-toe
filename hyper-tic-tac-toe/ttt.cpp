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

Field check_win(const Map & map, MapPos pos, size_t n, size_t a, size_t r)
{
	std::cout << "-- CHECK WIN --\n";
	vector<VMapPos> neighbours_offsets = get_neighbours_offsets(pos, n, a);
	int lines_count = 0;

	for (auto offset : neighbours_offsets)
	{
		if (check_line(map, pos, offset, n, a, r))
		{
			lines_count++;
			//return map[pos];
		}
	}

	if (lines_count == 0)
	{
		return EMPTY;
	}
	else
	{
		std::cout << lines_count << " LINES!\n";
		return map[pos];
	}
}

vector<VMapPos> get_neighbours_offsets(MapPos pos, size_t n, size_t a)
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
			else if (dim == 1 && pos + vector_to_pos(offset, n, a) > pos)
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
	// sprawdza czy pozycja + offset jest dopuszczalna i zwraca true lub false
}

bool check_line(const Map & map, MapPos pos, VMapPos offset, size_t n, size_t a, size_t r)
{
	if (map[pos] == EMPTY) return false;

	Field field = map[pos];
	int count = 1;
	int i = pos;

	//if (check(pos_to_vector(i), offset, false) && map[i + vector_to_pos(offset)] == field)
	//{
	//	std::cout << "In line with spos=" << pos << ", ipos=" << i << ", offset=" << vector_to_pos(offset) << ", field=" << field << "validation and field check passed (+)" << std::endl;
	//}
	while (valid_vectors_addition(pos_to_vector(i, n, a), offset, n, a) && 
		map[i + vector_to_pos(offset, n, a)] == field)
	{
		count++;
		i += vector_to_pos(offset, n, a);
		//std::cout << "ipos=" << i << ", count=" << count << std::endl;
	}
	
	i = pos;

	//if (check(pos_to_vector(i), offset, true) && map[i - vector_to_pos(offset)] == field)
	//{
	//	std::cout << "In line with spos=" << pos << ", ipos=" << i << ", offset=" << vector_to_pos(offset) << ", field=" << field << "validation and field check passed (-)" << std::endl;
	//}
	while (valid_vectors_subtraction(pos_to_vector(i, n, a), offset, n, a) &&
		map[i - vector_to_pos(offset, n, a)] == field)
	{
		count++;
		i -= vector_to_pos(offset, n, a);
		//std::cout << "ipos=" << i << ", count=" << count << std::endl;
	}

	if (count >= r) return true;

	return false;
}

