#include "ttt.h"
#include <vector>

size_t n = 3; // dimensions
size_t a = 5; // edge length
size_t r = a; // number of pawns in line to win

void write(const Map & map)
{
#ifdef _WIN32
	std::system("cls");
#else
	std::system("clear");
#endif

	//for (int i = 0; i < map.size(); i++)
	//{
	//	switch (map[i])
	//	{
	//	case EMPTY: cout << char(219); break;
	//	case O:		cout << "O"; break;
	//	case X:		cout << "X"; break;
	//	}

	//	if (i != 0 && (i + 1) % a == 0) cout << "\n";
	//	if (i != 0 && (i + 1) % (a * a) == 0) cout << "\n";
	//}

	int offset = 0;
	for (int i = 0; i < a; i ++)
	{
		for (int j = 0; j < a; j++)
		{
			for (int k = 0; k < a; k++)
			{
				switch (map[offset])
				{
				case EMPTY: cout << char(219); break;
				case O:		cout << "O"; break;
				case X:		cout << "X"; break;
				}
				offset++;
			}
			cout << " ";
			offset = offset - a + pow(a, n - 1);
		}
		cout << "\n";
		offset = (i+1)*a;
	}
	cout << "\n";
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
	// TODO: this functions doesnt't remove offsets that belong to the 
	// common line so check_line(...) may check the same line two times

	vector<int> offsets;

	function<void(size_t dim, int offset)> checker3;
	checker3 = [&](size_t dim, int offset)
	{
		vector<int> v = { 0 };
		if (!is_last_in_dim(offset, dim))
			v.push_back(1);
		if (!is_first_in_dim(offset, dim))
			v.push_back(-1);

		for (int i : v)
		{
			if (dim - 1 > 0)
			{
				checker3(dim - 1, offset + i * get_offset_by_dim(dim));
			}
			else if (offset + i != pos)
			{
				offsets.push_back(offset + i - pos);
			}
		}
	};
	
	checker3(n, pos);
	return offsets;
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

