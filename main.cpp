#include "ttt.h"

// initialized in ttt.cpp
extern size_t n;
extern size_t a;
extern size_t r;

int main(int argc, char ** argv)
{
	Map map(pow(a, n));

	for (int i = 0;; i = !i)
	{
		write(map);
		cout << "Player " << (i == 0 ? "X" : "O") << ": ";
		vector<size_t> v(n);
		do {
			for (int j = 0; j < n; j++)
			{
				std::cin >> v[j];
			}
		} while (!set_field(map, i == 0 ? X : O, v));

	}

	return 0;
}
