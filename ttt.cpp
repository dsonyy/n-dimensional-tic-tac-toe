#include "ttt.h"

size_t n = 2;
size_t a = 5;
size_t r = a;

void write(const Map & map)
{
	system("cls");

	for (int i = 0; i < map.size(); i++)
	{
		switch (map[i])
		{
		case EMPTY: cout << char(219); break;
		case O:		cout << "O"; break;
		case X:		cout << "X"; break;
		}

		if (i != 0 && (i + 1) % a == 0) cout << "\n";
		if (i != 0 && (i + 1) % (a * a) == 0) cout << "\n";
	}
}


int get_offset_by_dim(size_t dim)
{
	return pow(a, dim - 1);
}

bool is_first_in_dim(MapPos pos, size_t dim)
{
	return pos % int(pow(a, dim));
}

bool is_last_in_dim(MapPos pos, size_t dim)
{
	return (pos + 1) % int(pow(a, dim));
}

MapPos get_first_in_this_dim(MapPos pos, size_t dim)
{
	pos -= pos % size_t(pow(a, dim));
	return pos;
}

MapPos get_last_in_this_dim(MapPos pos, size_t dim)
{
	pos += pow(a, dim) - pos % size_t(pow(a, dim)) - 1;
	return pos;
}

VMapPos pos_to_vector(MapPos pos)
{
	VMapPos new_vpos(n);
	size_t N = n;

	while (N > 0)
	{
		new_vpos[N - 1] = pos / size_t(pow(a, n - 1));
		pos %= size_t(pow(a, n - 1));
		N--;
	}

	return new_vpos;
}

MapPos vector_to_pos(VMapPos vpos)
{
	size_t new_pos = 0;

	for (int i = 0; i < n; i++)
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
	if (!overwrite && map[pos] != EMPTY) return false;

	if (pos >= pow(a, n)) return false;

	map[pos] = field;
}

Field check_win(const Map & map, MapPos pos)
{
	vector<int> neighbours_offsets = get_neighbours_offsets(pos);

	return EMPTY;
}

vector<int> get_neighbours_offsets(MapPos pos)
{
	vector<int> offsets;

	function<void(size_t dim, int offset)> checker;
	checker = [&](size_t dim, int offset)
	{
		for (int i : {-1, 0, 1})
		{
			int deeper_offset = offset + i * get_offset_by_dim(dim);
			if (dim > 1)
			{
				checker(dim - 1, deeper_offset);
			}
			else if (deeper_offset > 0)
			{
				offsets.push_back(deeper_offset + pos);
			}
		}
	};

	checker(n, 0);

	return offsets;
}

bool check(const Map & map, MapPos pos, size_t dim, int offset)
{
	bool win = false;
	
	int noffset = offset;
	for (int i : {-1, 0, 1})
	{
		noffset = offset + get_offset_by_dim(dim) * i;
		if (dim > 1)
		{
			if (check(map, dim - 1, pos, noffset)) win = true;
		}
		else if (noffset != 0)
		{
			if (check_line(map, pos, noffset)) win = true; // win, but continues checking 
		}
	}

	return win;
};

bool check_line(const Map & map, MapPos pos, int offset)
{
	if (map[pos] == EMPTY) return false;

	Field field = map[pos];
	int count = 1;
	int i = pos;

	if (i + offset < pow(a, n) && i + offset >= 0)
	{
		while (map[i + offset] == field)
		{
			count++;
			i += offset;

			if (!((i + offset < pow(a, n) && i + offset >= 0))) break;
		}
	}

	i = pos;

	if (i - offset < pow(a, n) && i - offset >= 0)
	{
		while (map[i - offset] == field)
		{
			count++;
			i -= offset;
			if (!((i - offset < pow(a, n) && i - offset >= 0))) break;
		}
	}

	if (count >= r) return true;

	return false;
}

