#include "ttt.h"
#include <string>
#include <iostream>
#include <vector>

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Main.hpp>


//
//	CONSTANTS
//
/// WINDOW
const unsigned WIDTH = 720;
const unsigned HEIGHT = 480;
const std::string TITLE = "Hyper Tic-Tac-Toe";
const sf::Uint32 STYLE = sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize;
const sf::Int32 FRAME_RATE = 30;

extern size_t n;
extern size_t a;
extern size_t r;

//
//	GLOBALS
//
/// ENGINE
sf::RenderWindow window_;
bool running_ = true;
bool redraw_ = true;
sf::Clock clock_;
sf::Time next_tick_ = clock_.getElapsedTime();
bool keys_[sf::Keyboard::KeyCount];
/// GAMEPLAY
const float TileSize = 10;
const float TileNOffset = 7;
struct Tile
{
	size_t i;
	sf::RectangleShape rect;
};
std::vector<Tile> tiles_;
Map map_(pow(a, n));

//
//	HEADERS
//
void init_sfml();
void init_game();
void handle_input();
void update();
void redraw();


int main(int argc, char ** argv)
{
	init_sfml();
	init_game();

	while (running_)
	{
		handle_input();

		if (clock_.getElapsedTime() >= next_tick_)
		{
			update();
			redraw();

			next_tick_ += sf::milliseconds(1000 / FRAME_RATE);
		}

	}

	return 0;
}

void init_sfml()
{
	window_.create(sf::VideoMode(WIDTH, HEIGHT), TITLE, STYLE);
	window_.setMouseCursorVisible(true);
}

int f(int N)
{
	return ++N % 2 ? int(N / 2) : N / 2 - 1;
}

int dimoffset(int N)
{
	if (N == 0 || N == 1)
		return TileSize;
	else if (N == 2)
		return a * dimoffset(0) + TileNOffset;
	else
		return a * dimoffset(N - 2) + 2 * TileNOffset;
}

void init_game()
{
	for (size_t i = 0; i < map_.size(); i++)
	{
		VMapPos v = pos_to_vector(i);
		int x = 0, y = 0;
		for (size_t N = 0; N < n; N++)
		{
			if (N % 2 == 0)
			{
				x += v[N] * dimoffset(N);
			}
			else
			{
				y += v[N] * dimoffset(N);
			}


		}
		sf::RectangleShape rect(sf::Vector2f(TileSize, TileSize));
		rect.setPosition(x, y);

		tiles_.push_back({ i, rect });


		/*int x = 0, y = 0, j = i;
		for (int N = n; N > 0; N--)
		{
			if (N == 1)
			{
				x += j * (10 + 1);
			}
			else if (N == 2)
			{
				y += int(j / a) * (10 + 1);
			}
			else if (N % 2 == 1)
			{
				x += int(j / pow(a, N - 1)) * (10 + 1) * pow(a, f(N));
			}
			else
			{
				y += int(j / pow(a, N - 1)) * (10 + 1) * pow(a, f(N));
			}

			j %= int(pow(a, N - 1));
		}
		sf::RectangleShape rect(sf::Vector2f(10, 10));
		rect.setPosition(x, y);
		
		tiles_.push_back({ i, rect });
		*/
	}
}

void handle_input()
{
	sf::Event event;

	while (window_.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			running_ = false;
			break;
		case sf::Event::KeyPressed:
			keys_[event.key.code] = true;
			break;
		case sf::Event::KeyReleased:
			keys_[event.key.code] = false;
			break;
		case sf::Event::MouseMoved:
			break;
		}
	}
}

void update()
{
}


void redraw()
{
	if (redraw_)
	{
		window_.clear(sf::Color::Black);
		for (int i = 0; i < tiles_.size(); i++)
		{
			window_.draw(tiles_[i].rect);
		}

		window_.display();

		redraw_ = false;
	}
}