#pragma once
#include <functional>
#include <string>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Main.hpp>
#include "ttt.h"

struct State
{
	typedef std::string ID;

	ID id;
	std::function<void()> init;
	std::function<void()> update;
	std::function<void()> redraw;
	std::function<void()> handle_input;
};


void draw_turn(sf::RenderWindow & window, Field turn);
void draw_coords(sf::RenderWindow & window, VMapPos vpos, const sf::Font & font);