#include "ttt.h"

void write(const Map & map, size_t a)
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


size_t get_fields_num(size_t a, size_t n)
{
	return pow(a, n);
}

size_t get_offset_by_dim(size_t a, size_t n)
{
	return pow(a, n - 1);
}

bool is_first_in_dim(size_t pos, size_t a, size_t n)
{
	return pos % size_t(pow(a, n));
}

bool is_last_in_dim(size_t pos, size_t a, size_t n)
{
	return (pos + 1) % size_t(pow(a, n));
}

vector<size_t> pos_to_vector(size_t pos, size_t a, size_t n)
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

size_t vector_to_pos(vector<size_t> v, size_t a, size_t n)
{
	size_t pos = 0;

	for (int i = 0; i < n; i++)
	{
		pos += v[i] * a;
	}

	return pos;
}

