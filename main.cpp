#include "ttt.h"

// initialized in ttt.cpp
extern size_t n;
extern size_t a;
extern size_t r;

int main(int argc, char ** argv)
{
	Map map(pow(a, n));
	vector<size_t> v(n);

	write(map);

	set_field(map, O, 1);
	set_field(map, O, 4);
	set_field(map, O, 7);
	bool a = check(map, n, 1);


	for (int i = 0;; i = !i)
	{

		cout << "Player " << (i == 0 ? "O" : "X") << ": \n ";
		do {
			for (int j = 0; j < n; j++)
			{
				std::cin >> v[j];
			}
		} while (!set_field(map, i == 0 ? O : X, v));

		write(map);
		std::cout << check(map, n, vector_to_pos(v));
	}

	return 0;
}
