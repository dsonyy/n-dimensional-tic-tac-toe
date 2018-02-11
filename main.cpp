#include "ttt.h"

// initialized in ttt.cpp
extern size_t n;
extern size_t a;
extern size_t r;

int main(int argc, char ** argv)
{
	Map map(pow(a, n));
	VMapPos v(n);

	//write(map);

	for (int i = 0;; i = !i)
	{

		cout << "Player " << (i == 0 ? "O" : "X") << ": \n ";
		do {
			for (int j = 0; j < n; j++)
			{
				std::cin >> v[j];
			}
		} while (!set_field(map, i == 0 ? O : X, vector_to_pos(v)));

		//write(map);
		if (check_win(map, vector_to_pos(v)))
		{
			cout << "Player " << (i == 0 ? "O" : "X") << " won!\n";
			while (1);
		}
	}

	return 0;
}
