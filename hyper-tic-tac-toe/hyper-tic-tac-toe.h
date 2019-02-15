#pragma once
#include <functional>
#include <string>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Main.hpp>
#include "ttt.h"

const unsigned WIDTH = 720;
const unsigned HEIGHT = 480;
const std::string TITLE = "Hyper Tic-Tac-Toe";
const sf::Uint32 STYLE = sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize;
const sf::Int32 FRAME_RATE = 30;

const float TileSize = 18;
const float TileNOffset = 6;

const sf::Color BG_COLOR = sf::Color(0, 0, 20);
const sf::Color FG_COLOR = sf::Color(0, 0, 20);
const sf::Color TEXT_COLOR = sf::Color(255, 255, 255);
const sf::Color TEXT2_COLOR = sf::Color(100, 100, 100);
const sf::Color O_COLOR = sf::Color(255, 0, 0);
const sf::Color X_COLOR = sf::Color(0, 0, 255);
const sf::Color Y_COLOR = sf::Color(50, 50, 50);
const sf::Color Z_COLOR = sf::Color(255, 255, 0);



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
void draw_coords(sf::RenderWindow & window, VMapPos vpos);
void draw_dialog(sf::RenderWindow & window, std::string str, sf::Color color = TEXT_COLOR);