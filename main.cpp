#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;

enum Field { EMPTY, X, O };       
typedef std::vector<Field> Map;	  
typedef std::vector<size_t> Coord;

size_t n = 3;
size_t a = 3;
Map map(std::pow(a, n));

void write(const Map & map);

size_t map_coord(Coord v)
{
	int r = 0;
	for (int i = 0; i < v.size(); i++)
		r += *(v.begin() + i) * std::pow(a, i);
	return r;
}

Field get_field(Coord v)
{ 
	return map[map_coord(v)]; 
}

void set_field(Coord v, Field x) 
{ 
	if (get_field(v) == EMPTY) 
		map[map_coord(v)] = x; 
}

int main(int argc, char ** argv)
{
	for (int i = 0;; i++)
	{
		write(map);
		std::cout << "Gracz " << i % 2 << ": ";
		Coord v(n);
		for (int j = 0; j < n; j++)
		{
			std::cin >> v[j];
		}
		set_field(v, i % 2 ? X : O);
	
	}

	auto check = [](Coord v)->bool
	{
		if (v[0] > 0 && map[map_coord(v) - 1] == EMPTY)
		{
			return true;
		}

		return false;
	};

	write(map);

	while (1);
	return 0;
}


void write(const Map & map)
{
	std::system("cls");

	for (int i = 0; i < map.size(); i++)
	{
		switch (map[i])
		{
		case EMPTY: std::cout << char(219); break;
		case O:		std::cout << "X"; break;
		case X:		std::cout << "O"; break;
		}

		if (i != 0 && (i + 1) % a == 0) std::cout << "\n";
		if (i != 0 && (i + 1) % (a * a) == 0) std::cout << "\n";
	}

}