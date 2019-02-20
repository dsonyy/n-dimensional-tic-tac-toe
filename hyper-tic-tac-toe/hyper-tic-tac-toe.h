#pragma once
#include <functional>
#include <string>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Main.hpp>
#include "ttt.h"
#include <memory>
/*
	dimensions	 max edge  
		10			2
		9			2
		8			3 -___-
		7			3
		6			4
		5			6 -___-
		4			8
		3			14
		2			75 -___-

*/



const unsigned WIDTH = 720;
const unsigned HEIGHT = 480;
const std::string TITLE = "Hyper Tic-Tac-Toe";
const sf::Uint32 STYLE = sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize;
const sf::Int32 FRAME_RATE = 60;

const float TILE_SIZE = 9;
const float TileNOffset = 6;

const float MOVE_SPEED = 4;

const sf::Color BG_COLOR = sf::Color(30, 0, 40);
const sf::Color FG_COLOR = sf::Color(180, 180, 180);
const sf::Color TEXT_COLOR = sf::Color(255, 255, 255);
const sf::Color TEXT2_COLOR = sf::Color(100, 100, 100);
const sf::Color O_COLOR = sf::Color(255, 0, 0);
const sf::Color X_COLOR = sf::Color(0, 0, 255);
const sf::Color Y_COLOR = sf::Color(50, 50, 50);
const sf::Color Z_COLOR = sf::Color(0, 180, 0);

const sf::Vector2f MENU_WINDOW_SIZE = sf::Vector2f(270, 400);
const sf::Vector2f MENU_BUTTON_SIZE = sf::Vector2f(30, 30);
const sf::Vector2f MENU_WIDGET_OFFSET = sf::Vector2f(20, 50);

const size_t MAX_N = 10;

const std::string FONT_NAME = "cour.ttf";
const int FONT_SIZE = 18;
const int FONT2_SIZE = 12;

typedef int State;
const State STATE_MENU = 0;
const State STATE_GAME = 1;


struct Tile
{
	size_t i;
	sf::RectangleShape rect;
	VMapPos dim;
};

template<typename ActionType>
struct Button
{
	typedef std::string ID;

	ID id;
	sf::Text text;
	std::function<ActionType> action;
	sf::Vector2f pos;
	sf::Vector2f size;
	bool hovered = false;
	bool clicked = false;
	bool released = false;
};

//struct State
//{
//	typedef std::string ID;
//
//	ID id;
//	std::function<void()> init;
//	std::function<void()> update;
//	std::function<void()> redraw;
//	std::function<void()> handle_input;
//};

struct S
{
	State id;
};

struct Program
{
	sf::RenderWindow window;
	sf::Font font;
	bool keys[sf::Keyboard::KeyCount];
	bool redraw;
	bool running;
	bool update;
	State state;
	State next_state;
	sf::Clock clock;
	sf::Time next_tick;
};

struct Settings
{
	size_t p = 2;
	size_t n = 2;
	size_t a = 3;
	size_t r = 3;
};

typedef Button<void(Settings &)> SettingsButton;

struct Game
{
	size_t p;
	size_t n;
	size_t a;
	size_t r;
	Map map;
	std::vector<Tile> tiles;
	sf::Vector2f tiles_offset;
	Field turn;
	VMapPos pos;
	bool quit;
};

struct Menu
{
	// Design
	sf::RectangleShape window;
	sf::RectangleShape shadow;
	
	sf::Text title;
	sf::Text subtitle;
	
	sf::Text header_players;
	sf::Text header_dimensions;
	sf::Text header_edges;
	sf::Text header_line;
	sf::Text header_target;

	Settings settings;

	bool quit;

	std::vector<SettingsButton> buttons;
	Button<void(Menu &)> start_game;
};


void init_program(Program & program);

void init_menu(Program & program, Menu & menu);
void update_menu(Program & program, Menu & menu);
void redraw_menu(Program & program, Menu & menu);
void handle_input_menu(Program & program, Menu & menu);

bool is_in(sf::Vector2f pos, const Tile & tile);
bool is_in(sf::Vector2f mouse, sf::Vector2f pos, sf::Vector2f size);
int dimoffset(int N, const size_t a);

void init_game(Game & game);
void init_game(Game & game, size_t p, size_t n, size_t a, size_t r);
void handle_input_game(Program & program, Game & game);
void update_game(Program & program, Game & game);
void redraw_game(Program & program, Game & game);

void draw_map(Program & program, const Game & game);
void draw_turn(Program & program, Field turn);
void draw_coords(Program & program, VMapPos vpos);
void draw_dialog(Program & program, std::string str, sf::Color color);
void draw_legend(Program & program);

void handle_close(const sf::Event & event, Program & program);
void handle_key_pressed(const sf::Event & event, Program & program);
void handle_key_released(const sf::Event & event, Program & program);
void handle_resize(const sf::Event & event, Program & program);
