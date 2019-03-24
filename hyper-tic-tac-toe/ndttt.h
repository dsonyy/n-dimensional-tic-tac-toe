
#pragma once
#include <functional>
#include <string>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Main.hpp>
#include "ttt.h"
#include <memory>
#include <array>



const unsigned WIDTH = 720;
const unsigned HEIGHT = 480;
const std::string TITLE = "Hyper Tic-Tac-Toe";
const sf::Uint32 STYLE = sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize;
const sf::Int32 FRAME_RATE = 60;

float TILE_SIZE = 24;
float MAX_TILE_SIZE = 30;
float MIN_TILE_SIZE = 7;
const float TILE_N_OFFSET = 6;

const float MOVE_SPEED = 4;

const sf::Color BG_COLOR = sf::Color(30, 0, 40);
const sf::Color BG2_COLOR = sf::Color(0, 0, 20);
const sf::Color FG_COLOR = sf::Color(180, 180, 180);
const sf::Color TEXT_COLOR = sf::Color(255, 255, 255);
const sf::Color TEXT2_COLOR = sf::Color(100, 100, 100);
const sf::Color O_COLOR = sf::Color(255, 0, 0);
const sf::Color X_COLOR = sf::Color(0, 0, 255);
const sf::Color Y_COLOR = sf::Color(50, 50, 50);
const sf::Color Z_COLOR = sf::Color(0, 180, 0);

const sf::Vector2f MENU_WINDOW_SIZE = sf::Vector2f(270, 350);
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
	bool hovered = false;
	bool clicked = false;
};

template<typename ActionType>
struct Button
{
	typedef std::string ID;

	ID id;
	sf::Text text;
	bool hovered = false;
	bool clicked = false;
	bool selected = false;
	bool active = true;
	std::function<ActionType> action;
	sf::Vector2f pos;
	sf::Vector2f size;
};

struct Dialog
{
	std::string str;
	sf::Color color;
};

struct Program
{
	sf::RenderWindow window;
	sf::Font font;
	bool keys[sf::Keyboard::KeyCount];
	bool redraw = true;
	bool running = true;
	bool update = true;
	State state;
	State next_state;
	sf::Clock clock;
	sf::Time next_tick;
};

struct Game
{
	size_t p;
	size_t n;
	size_t a;
	size_t r;
	size_t l;
	Map map;
	std::array<int, MAX_PLAYERS> scores = {};
	std::vector<Tile> tiles;
	sf::Vector2f tiles_offset;
	size_t tiles_size = TILE_SIZE;
	Field turn;
	VMapPos pos;
	Dialog dialog;
	std::vector<VMapPos> neighbours_offsets;
	bool show_dialog = false;
	bool quit;
};

struct Menu
{
	// Design
	sf::RectangleShape window;
	sf::RectangleShape shadow;
	
	size_t p = 2;
	size_t n = 3;
	size_t a = 3;
	size_t r = 3;

	bool quit;
	bool new_game = true;

	std::vector<sf::Text> texts;
	std::vector<Button<void(Menu &)>> buttons;
};


void init_program(Program & program);

void init_menu(Program & program, Menu & menu);
void update_menu(Program & program, Menu & menu);
void redraw_menu(Program & program, Menu & menu);
void handle_input_menu(Program & program, Menu & menu);

bool is_in(sf::Vector2f mouse, sf::Vector2f pos, sf::Vector2f size);
int dimoffset(int N, const size_t a, size_t tile_size);
void create_tiles(Game & game, size_t size);

void init_game(Game & game);
void init_game(Game & game, size_t p, size_t n, size_t a, size_t r);
void handle_input_game(Program & program, Game & game);
void update_game(Program & program, Game & game);
void redraw_game(Program & program, Game & game);

void draw_map(Program & program, const Game & game);
void draw_turn(Program & program, Field turn);
void draw_coords(Program & program, VMapPos vpos);
void draw_dialog(Program & program, Dialog dialog);
void draw_legend(Program & program);
void draw_scores(Program & program, Game & game);

void handle_close(const sf::Event & event, Program & program);
void handle_resize(const sf::Event & event, Program & program);
void handle_key_pressed(const sf::Event & event, Program & program);
void handle_key_released(const sf::Event & event, Program & program);

sf::Text get_text(std::string str, sf::Color color, int size,
	sf::Vector2f pos, const Program & program);

Button<void(Menu &)> get_settings_button(std::string str, sf::Vector2f pos,
	std::string id, const Program & program);

void deactive_buttons(Menu & menu, std::string id);
bool action_button(Menu & menu, std::string id);
