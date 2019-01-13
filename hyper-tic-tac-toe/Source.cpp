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

void init_game()
{

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
		for (int i = 0; i < map_.size(); i++)
		{
			int k = 0;
			int x = 0, y = 0;	
			int j = i;
			for (int N = n; N > 0; N--)
			{
				if (N % 2 == 1)
				{
					x += int(j / pow(a, N - 1)) * 10;
				}
				else
				{
					y += int(j / pow(a, N - 1)) * 10;
					k++;
				}
				j %= int(pow(a, N - 1));
			}
			sf::RectangleShape rect(sf::Vector2f(9, 9));
			rect.setPosition(x, y);
			window_.draw(rect);
		}

		window_.display();

		redraw_ = false;
	}
}