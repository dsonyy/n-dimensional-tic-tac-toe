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

extern size_t n;
extern size_t a;
extern size_t r;

int main(int argc, char ** argv)
{
	Map map(pow(a, n));

	for (int i = 0;; i = !i)
	{
		write(map);
		std::cout << "Player " << i << ": ";
		vector<size_t> v(n);
		for (int j = 0; j < n; j++)
		{
			std::cin >> v[j];
		}
		//set_field(v, i % 2 ? X : O);
	}

	//auto check = [](Coord v)->bool
	//{
	//	if (v[0] > 0 && map[map_coord(v) - 1] == EMPTY)
	//	{
	//		return true;
	//	}

	//	return false;
	//};

	//write(map);

	while (1);
	return 0;
}
