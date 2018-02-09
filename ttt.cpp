#include "ttt.h"

size_t n = 3;
size_t a = 3;
size_t r = 3;

void write(const Map & map)
{
	system("cls");

	for (int i = 0; i < map.size(); i++)
	{
		switch (map[i])
		{
		case EMPTY: cout << char(219); break;
		case O:		cout << "X"; break;
		case X:		cout << "O"; break;
		}

		if (i != 0 && (i + 1) % a == 0) cout << "\n";
		if (i != 0 && (i + 1) % (a * a) == 0) cout << "\n";
	}

}


size_t get_offset_by_dim(size_t dim)
{
	return pow(a, dim - 1);
}

bool is_first_in_dim(size_t pos, size_t dim)
{
	return pos % size_t(pow(a, dim));
}

bool is_last_in_dim(size_t pos, size_t dim)
{
	return (pos + 1) % size_t(pow(a, dim));
}

size_t get_first_in_this_dim(size_t pos, size_t dim)
{
	pos -= pos % size_t(pow(a, dim));
	return pos;
}

size_t get_last_in_this_dim(size_t pos, size_t dim)
{
	pos += pow(a, dim) - pos % size_t(pow(a, dim)) - 1;
	return pos;
}

vector<size_t> pos_to_vector(size_t pos)
{
	vector<size_t> v(n);
	size_t N = n;

	while (N > 0)
	{
		v[N - 1] = pos / size_t(pow(a, n - 1));
		pos %= size_t(pow(a, n - 1));
		N--;
	}

	return v;
}

size_t vector_to_pos(vector<size_t> v)
{
	size_t pos = 0;

	for (int i = 0; i < n; i++)
	{
		pos += v[i] * size_t(pow(a, i));
	}

	return pos;
}

Field get_field(const Map & map, vector<size_t> v)
{
	return map[vector_to_pos(v)];
}

Field get_field(const Map & map, size_t pos)
{
	return map[pos];
}

bool set_field(Map & map, Field field, vector<size_t> v, bool overwrite)
{
	for (auto i : v)
	{
		if (i < 0 || i >= a) return false;
	}

	return set_field(map, field, vector_to_pos(v), overwrite);
}

bool set_field(Map & map, Field field, size_t pos, bool overwrite)
{
	if (!overwrite && map[pos] != EMPTY) return false;

	if (pos >= pow(a, n)) return false;

	map[pos] = field;
}

bool check_win(const Map & map, vector<size_t> v)
{
	for (auto i : v)
	{
		if (i < 0 || i >= a) return false;
	}

	return check_win(map, vector_to_pos(v));
}

bool check_win(const Map & map, size_t pos)
{
	if (map[pos] == EMPTY) return false;

	Field field = map[pos];
	size_t count = 1;
	size_t i = pos;
	size_t dim = 1;

	//if ()
	{
		while (map[i + pow(a, dim)] == field)
		{
			count++;
			i++;
		}
	}

	i = pos;

	//if ()
	{
		while (map[i - pow(a, dim)] == field)
		{
			count++;
			i--;
		}
	}

	if (count >= r) return true;

	return false;
}

