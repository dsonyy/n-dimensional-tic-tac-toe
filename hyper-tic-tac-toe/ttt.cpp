#include "ttt.h"
#include <iostream>
#include <vector>
#include <functional>
#include <cstdlib>
#include <cmath>

size_t n = 3; // dimensions
size_t a = 3; // edge length
size_t r = a; // number of pawns in line to win

using namespace std;

void write(const Map & map)
{
#ifdef _WIN32
	std::system("cls");
#else
	std::system("clear");
#endif

	for (int i = 0; i < map.size(); i++)
	{
		switch (map[i])
		{
		case EMPTY: cout << char(219); break;
		case O:		cout << "O"; break;
		case X:		cout << "X"; break;
		case Y:		cout << "Y"; break;
		case Z:		cout << "Z"; break;
		}

		if (i != 0 && (i + 1) % a == 0) cout << "\n";
		if (i != 0 && (i + 1) % (a * a) == 0) cout << "\n";
	}

	//int offset = 0;
	//for (int i = 0; i < a; i ++)
	//{
	//	for (int j = 0; j < a; j++)
	//	{
	//		for (int k = 0; k < a; k++)
	//		{
	//			switch (map[offset])
	//			{
	//			case EMPTY: cout << char(219); break;
	//			case O:		cout << "O"; break;
	//			case X:		cout << "X"; break;
	//			}
	//			offset++;
	//		}
	//		cout << " ";
	//		offset = offset - a + pow(a, n - 1);
	//	}
	//	cout << "\n";
	//	offset = (i+1)*a;
	//}
	//cout << "\n";

	//int offset = 0;
	//int jump = 1;
	//int dim = 1;
	//while (offset < map_length())
	//{
	//	for (int i = 0; i < a; i++)
	//	{
	//		jump += pow(a, dim - 1);
	//	}
	//	dim++;
	//}

}

int map_length()
{
	return pow(a, n);
}

int get_offset_by_dim(size_t dim)
{
	return pow(a, dim - 1);
}

bool is_first_in_dim(MapPos pos, size_t dim)
{
	return pos % int(pow(a, dim)) < pow(a, dim-1);
}

bool is_last_in_dim(MapPos pos, size_t dim)
{
	return pos % int(pow(a, dim)) >= (a - 1) * pow(a, dim - 1);
}

VMapPos pos_to_vector(MapPos pos)
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

MapPos vector_to_pos(VMapPos vpos)
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

bool set_field(Map & map, Field field, MapPos pos, bool overwrite)
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

Field check_win(const Map & map, MapPos pos)
{
	// prepare offsets that are relative to the checked field (variable pos),
	// ignore invalid, out of dimension and equal to 0 offsets
	vector<int> neighbours_offsets = get_neighbours_offsets(pos);

	for (auto offset : neighbours_offsets)
	{
		if (check_line(map, pos, offset))
		{
			return map[pos];
		}
	}

	return EMPTY;
}

vector<int> get_neighbours_offsets(MapPos pos)
{
	// TODO: this function doesnt't remove offsets that belong to the 
	// common line so check_line(...) may check the same line two times

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
			else if (dim == 1 && pos + vector_to_pos(offset) > pos)
			{
				offsets.push_back(offset);
			}
			
			
		}
	};
	
	checker(n, VMapPos(n, 0));
	return vector<int>();
}

bool check_line(const Map & map, MapPos pos, int offset)
{
	if (map[pos] == EMPTY) return false;

	Field field = map[pos];
	int count = 1;
	int i = pos;

	while (i + offset < map_length() && i + offset >= 0 &&
		map[i + offset] == field)
	{
		count++;
		i += offset;
	}
	
	i = pos;

	while (i - offset < map_length() && i - offset >= 0 && 
		map[i - offset] == field)
	{
		count++;
		i -= offset;
	}

	if (count >= r) return true;

	return false;
}

