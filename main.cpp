#include "ttt.h"

//size_t map_coord(Coord v)
//{
//	int r = 0;
//	for (int i = 0; i < v.size(); i++)
//		r += *(v.begin() + i) * std::pow(a, i);
//	return r;
//}
//
//Field get_field(Coord v)
//{ 
//	return map[map_coord(v)]; 
//}
//
//void set_field(Coord v, Field x) 
//{ 
//	if (get_field(v) == EMPTY) 
//		map[map_coord(v)] = x; 
//}

int main(int argc, char ** argv)
{
	size_t n = 3;
	size_t a = 3;
	size_t r = 3;
	Map map(pow(a, n));

	for (int i = 0;; i = !i)
	{
		write(map, a);
		std::cout << "Player " << i << ": ";
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
