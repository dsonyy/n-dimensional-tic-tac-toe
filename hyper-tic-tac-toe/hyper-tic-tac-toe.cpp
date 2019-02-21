#include "ttt.h"
#include "hyper-tic-tac-toe.h"
#include <string>
#include <iostream>
#include <vector>
#include <functional>

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Main.hpp>

//
//	Entry point
//
int main(int argc, char ** argv)
{
	// Init program data
	Program program;
	init_program(program);

	// Init states data
	Game game;
	Menu menu;
	init_game(game);
	init_menu(program, menu);

	// Run main game loop
	while (program.running)
	{
		// States handles their input
		switch (program.state)
		{
		case STATE_GAME: 
			handle_input_game(program, game); 
			if (game.quit)
			{
				program.state = STATE_MENU;
				menu.quit = false;
			}
			break;
		case STATE_MENU: 
			handle_input_menu(program, menu); 
			if (menu.quit)
			{
				init_game(game, menu.p, menu.n, menu.a, menu.r);
				program.state = STATE_GAME;
				game.quit = false;
			}
		break;
		}

		

		// States updates themselfes with specified timing
		if (program.clock.getElapsedTime() >= program.next_tick)
		{
			if (program.update)
			{
				switch (program.state)
				{
				case STATE_GAME: update_game(program, game); break;
				case STATE_MENU: update_menu(program, menu); break;
				}
			}

			program.next_tick += sf::milliseconds(1000 / FRAME_RATE);
		}

		// States redraw themselfes
		if (program.redraw)
		{
			switch (program.state)
			{
			case STATE_GAME: redraw_game(program, game); break;
			case STATE_MENU: redraw_menu(program, menu); break;
			}
			program.window.display();
		}
	}

	return 0;
}

sf::Text get_text(std::string str, sf::Color color, int size, 
	sf::Vector2f pos, const Program & program)
{
	sf::Text t;
	t.setString(str);
	t.setFont(program.font);
	t.setCharacterSize(size);
	t.setStyle(sf::Text::Bold);
	t.setFillColor(color);
	t.setPosition(pos);
	t.setOutlineThickness(2);
	t.setOutlineColor(BG_COLOR);

	return t;
}

SettingsButton get_settings_button(std::string str, sf::Vector2f pos, 
	std::string id, const Program & program)
{
	auto b = SettingsButton();
	b.action = [](Menu &) {};

	b.id = id;
	b.text = get_text(str, sf::Color::White, FONT_SIZE, pos, program);
	b.pos = pos - sf::Vector2f(3, 3);
	b.size = sf::Vector2f(b.text.getLocalBounds().width + 6, 
		b.text.getLocalBounds().height + 6);

	return b;
}

//
// STATE MENU
//
void init_menu(Program & program, Menu & menu)
{
	auto origin = sf::Vector2f((program.window.getSize().x - MENU_WINDOW_SIZE.x) / 2,
		(program.window.getSize().y - MENU_WINDOW_SIZE.y) / 2);
	
	menu.quit = false;

	menu.window.setSize(MENU_WINDOW_SIZE);
	menu.window.setFillColor(FG_COLOR);
	menu.window.setPosition(origin);

	menu.shadow = menu.window;
	menu.shadow.move(10, 10);
	menu.shadow.setFillColor(sf::Color(40, 40, 60));
	menu.shadow.setPosition(origin + sf::Vector2f(10, 10));

	menu.texts.push_back(get_text("HYPER TIC-TAC-TOE", sf::Color::White, 20,
		origin + sf::Vector2f(20, 10), program));

	menu.texts.push_back(get_text("by dsonyy", sf::Color(200, 200, 230), FONT2_SIZE,
		origin + sf::Vector2f(170, 33), program));

	menu.texts.push_back(get_text("Players:", sf::Color(200, 200, 230), FONT2_SIZE,
		origin + sf::Vector2f(20, 60), program));

	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		auto b = get_settings_button(std::to_string(i + 1), 
			origin + sf::Vector2f(30 + (i * 20), 80), "p" + std::to_string(i + 1), program);
		b.action = [i](Menu & m) { m.p = i + 1; };
		menu.buttons.push_back(b);
	}

	menu.texts.push_back(get_text("Dimensions:", sf::Color(200, 200, 230), FONT2_SIZE,
		origin + sf::Vector2f(20, 110), program));

	for (int i = 0; i < MAX_N; i++)
	{
		auto b = get_settings_button(std::to_string(i + 1),
			origin + sf::Vector2f(30 + (i * 20), 130), "n" + std::to_string(i + 1), program);
		b.action = [i](Menu & m) { m.n = i + 1; };
		menu.buttons.push_back(b);
	}

	menu.texts.push_back(get_text("Edge length:", sf::Color(200, 200, 230), FONT2_SIZE,
		origin + sf::Vector2f(20, 160), program));

	for (int i : { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50})
	{
		auto b = get_settings_button(std::to_string(i),
			origin + (i <= 10 ? sf::Vector2f(30 + (i-1) * 20, 180) : sf::Vector2f(30 + (i/10-2) * 60, 200)),
			"a" + std::to_string(i), program);
		b.action = [i](Menu & m) { m.a = i; };
		menu.buttons.push_back(b);
	}

	menu.texts.push_back(get_text("Winning line length:", sf::Color(200, 200, 230), FONT2_SIZE,
		origin + sf::Vector2f(20, 230), program));

	for (int i = 0; i < 10; i++)
	{
		auto b = get_settings_button(std::to_string(i + 1),
			origin + sf::Vector2f(30 + (i * 20), 250), "r" + std::to_string(i + 1), program);
		b.action = [i](Menu & m) { m.r = i; };
		menu.buttons.push_back(b);
	}

	menu.texts.push_back(get_text("Lines to win:", sf::Color(200, 200, 230), FONT2_SIZE,
		origin + sf::Vector2f(20, 280), program));

	int count = 0;
	for (int i : {1, 3, 5, 7, 9})
	{
		auto b = get_settings_button(std::to_string(i),
			origin + sf::Vector2f(30 + (count * 20), 300), "l" + std::to_string(i), program);
		b.action = [i](Menu & m) { m.l = i; };
		menu.buttons.push_back(b);
		count++;
	}
	
	auto b = get_settings_button("Unlimited",
		origin + sf::Vector2f(130, 300), "l0", program);
	b.action = [](Menu & m) { m.l = 0; };
	menu.buttons.push_back(b);

	b = get_settings_button("Start new game", origin + sf::Vector2f(50, 345), 
		"start", program);
	b.action = [](Menu & m) { m.quit = true; };
	menu.buttons.push_back(b);
}

void handle_input_menu(Program & program, Menu & menu)
{
	sf::Event event;

	while (program.window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed: 
			{
				handle_close(event, program);
				break;
			}
			case sf::Event::Resized: 
			{	
				handle_resize(event, program);
				auto origin = sf::Vector2f((program.window.getSize().x - MENU_WINDOW_SIZE.x) / 2,
					(program.window.getSize().y - MENU_WINDOW_SIZE.y) / 2);
				break;
			}	
			case sf::Event::MouseButtonPressed:
			{
				auto pos = sf::Vector2f(sf::Mouse::getPosition(program.window));
				for (auto & b : menu.buttons)
				{
					if (is_in(pos, b.pos, b.size))
						b.text.setFillColor(sf::Color::Red);
					else
						b.text.setFillColor(sf::Color::White);
				}
				program.redraw = true;
				break;
			}
			case sf::Event::MouseButtonReleased:
			{
				auto pos = sf::Vector2f(sf::Mouse::getPosition(program.window));
				for (auto & b : menu.buttons)
				{
					if (is_in(pos, b.pos, b.size))
						b.action(menu);
					else
						b.action(menu);
				}
				program.redraw = true;
				break;
			}
			case sf::Event::MouseMoved:
			{
				auto pos = sf::Vector2f(sf::Mouse::getPosition(program.window));
				for (auto & b : menu.buttons)
				{
					if (is_in(pos, b.pos, b.size))
					{
						b.text.setFillColor(sf::Color::Yellow);
						b.text.setStyle(sf::Text::Bold | sf::Text::Underlined);
					}
					else
					{
						b.text.setFillColor(sf::Color::White);
						b.text.setStyle(sf::Text::Bold);
					}
				}
				program.redraw = true;
			}
			break;
		}
	}
 
}

void update_menu(Program & program, Menu & menu)
{

}

void redraw_menu(Program & program, Menu & menu)
{
	program.window.clear(BG_COLOR);

	program.window.draw(menu.shadow);
	program.window.draw(menu.window);
	draw_legend(program);
	for (const auto & t : menu.texts)
	{
		program.window.draw(t);
	}
	for (const auto & b : menu.buttons)
	{
		program.window.draw(b.text);
	}
	
	program.redraw = false;
}

//
// STATE GAME
//
void init_game(Game & game)
{
	init_game(game, 2, 2, 3, 3);
}

void init_game(Game & game, size_t p, size_t n, size_t a, size_t r)
{
	game.quit = false;
	game.map = Map(std::pow(a, n), EMPTY);
	game.turn = O;

	for (size_t i = 0; i < game.map.size(); i++)
	{
		VMapPos v = pos_to_vector(i, n, a);
		int x = 0, y = 0;
		sf::Color color = sf::Color::White;
		for (size_t N = 0; N < n; N++)
		{
			if (N % 2 == 0)
			{
				x += v[N] * dimoffset(N, a);
			}
			else
			{
				y += v[N] * dimoffset(N, a);
			}
		}
		sf::RectangleShape rect(sf::Vector2f(TILE_SIZE, TILE_SIZE));
		rect.setFillColor(color);
		rect.setPosition(x, y);

		game.tiles.push_back({ i, rect, pos_to_vector(i, n, a) });

	}

	game.p = p;
	game.n = n;
	game.a = a;
	game.r = r;
}

void handle_input_game(Program & program, Game & game)
{
	sf::Event event;

	while (program.window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:			handle_close(event, program);			break;
		case sf::Event::KeyPressed:		handle_key_pressed(event, program);		if (event.key.code == sf::Keyboard::Key::Escape) game.quit = true; break;
		case sf::Event::KeyReleased:	handle_key_released(event, program);	break;
		case sf::Event::MouseButtonPressed:
		{	
			auto pos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
		for (auto & t : game.tiles)
		{
			if (is_in(pos - game.tiles_offset, t))
			{
				t.rect.setFillColor(sf::Color(100, 100, 100));
				if (game.map[t.i] == EMPTY)
				{
					game.map[t.i] = game.turn;
					game.turn = Field((int(game.turn) + 1) % game.p);
					//auto win = check_win(game.map, t.i);
					//switch (win)
					//{
					//case O:
					//	std::cout << "Player Red created a line!" << std::endl;
					//	break;
					//case X:
					//	std::cout << "Player Blue created a line!" << std::endl;
					//	break;
					//case Y:
					//	std::cout << "Player Y created a line!" << std::endl;
					//	break;
					//case Z:
					//	std::cout << "Player Z created a line!" << std::endl;
					//	break;
					//}
				}
			}
			else
			{
				t.rect.setFillColor(sf::Color::White);
			}

		}
		program.redraw = true;

		break;
		}
		case sf::Event::MouseButtonReleased:
		case sf::Event::MouseMoved:
		{
			auto pos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				for (auto & t : game.tiles)
				{
					if (is_in(pos - game.tiles_offset, t))
					{
						t.rect.setFillColor(sf::Color(200, 200, 200));
					}
					else
					{
						t.rect.setFillColor(sf::Color::White);
					}

				}
				program.redraw = true;
			}
			break;
		}
		case sf::Event::Resized: handle_resize(event, program); break;
		}
	}
}

void update_game(Program & program, Game & game)
{
	if (program.keys[sf::Keyboard::Up] == true || program.keys[sf::Keyboard::W] == true)
	{
		game.tiles_offset.y += MOVE_SPEED;
		program.redraw = true;
	}
	if (program.keys[sf::Keyboard::Down] == true || program.keys[sf::Keyboard::S] == true)
	{
		game.tiles_offset.y -= MOVE_SPEED;
		program.redraw = true;
	}
	if (program.keys[sf::Keyboard::Left] == true || program.keys[sf::Keyboard::A] == true)
	{
		game.tiles_offset.x += MOVE_SPEED;
		program.redraw = true;
	}
	if (program.keys[sf::Keyboard::Right] == true || program.keys[sf::Keyboard::D] == true)
	{
		game.tiles_offset.x -= MOVE_SPEED;
		program.redraw = true;
	}
}

void redraw_game(Program & program, Game & game)
{
	program.window.clear(BG2_COLOR);

	draw_map(program, game);
	draw_turn(program, game.turn);
	draw_coords(program, game.pos);
	draw_legend(program);

	program.redraw = false;
}

//
//	Draw functions for STATE GAME
//
void draw_map(Program & program, const Game & game)
{
	auto circle = sf::CircleShape(TILE_SIZE / 2 - 1);
	
	for (int i = 0; i < game.tiles.size(); i++)
	{
		auto rect = game.tiles[i].rect;
		rect.move(game.tiles_offset);
		program.window.draw(rect);


		circle.setPosition(rect.getPosition() + sf::Vector2f(1, 1));
		switch (game.map[game.tiles[i].i])
		{
		case O:
		{
			circle.setFillColor(O_COLOR);
			program.window.draw(circle);
			break;
		}
		case X:
		{
			circle.setFillColor(X_COLOR);
			program.window.draw(circle);
			break;
		}
		case Y:
		{
			circle.setFillColor(Y_COLOR);
			program.window.draw(circle);
			break;
		}
		case Z:
		{
			circle.setFillColor(Z_COLOR);
			program.window.draw(circle);
			break;
		}
		}
	}
}

void draw_turn(Program & program, Field turn)
{
	auto circle = sf::CircleShape(15);
	circle.setPosition(sf::Vector2f(program.window.getSize().x - 62, 20));
	circle.setOutlineThickness(4);
	circle.setOutlineColor(BG2_COLOR);
	switch (turn)
	{
	case O:
	{
		auto c = O_COLOR;
		circle.setFillColor(sf::Color(c.r, c.g, c.b, 200));
		break;
	}
	case X:
	{
		auto c = X_COLOR;
		circle.setFillColor(sf::Color(c.r, c.g, c.b, 200));
		break;
	}
	case Y:
	{
		auto c = Y_COLOR;
		circle.setFillColor(sf::Color(c.r, c.g, c.b, 200));
		break;
	}
	case Z:
	{
		auto c = Z_COLOR;
		circle.setFillColor(sf::Color(c.r, c.g, c.b, 200));
		break;

	}
	}

	program.window.draw(circle);
}

void draw_coords(Program & program, VMapPos vpos)
{
	auto value = sf::Text();
	value.setCharacterSize(FONT_SIZE);
	value.setFont(program.font);
	value.setPosition(program.window.getSize().x - 40,  40);
	value.setFillColor(TEXT_COLOR);
	value.setOutlineColor(BG2_COLOR);
	value.setStyle(sf::Text::Bold);
	value.setOutlineThickness(3);

	auto dim = value;
	dim.setFillColor(TEXT2_COLOR);
	dim.move(-25, 0);


	for (int i = 0; i < vpos.size(); i++)
	{
		dim.setString(std::to_string(i + 1) + ": ");
		value.setString(std::to_string(vpos[i]));
		dim.move(0, 20);
		value.move(0, 20);
		program.window.draw(value);
		program.window.draw(dim);
	}
}

void draw_dialog(Program & program, std::string str, sf::Color color)
{
	auto text = sf::Text(str, program.font, FONT_SIZE);
	text.setFillColor(color);
	text.setOutlineColor(BG2_COLOR);
	text.setOutlineThickness(2);
	text.setStyle(sf::Text::Bold);
	text.setPosition(program.window.getSize().x  / 2 - text.getLocalBounds().width / 2, 20);

	program.window.draw(text);
}

void draw_legend(Program & program)
{ 
	sf::Text text;

	if (program.state == STATE_GAME)
		text = sf::Text("Arrows/WASD - Move camera    Mouse Left - Select field    ESC - Show menu", program.font, FONT2_SIZE);
	else if (program.state == STATE_MENU)
		text = sf::Text("ESC - Back to game", program.font, FONT2_SIZE);

	text.setFillColor(TEXT2_COLOR);
	text.setOutlineColor(BG2_COLOR);
	text.setStyle(sf::Text::Bold);
	text.setOutlineThickness(2);
	text.setPosition(5, program.window.getSize().y - 18);

	program.window.draw(text);
}


//
//	Input handlers
//
void handle_close(const sf::Event & event, Program & program)
{
	program.running = false;
}

void handle_key_pressed(const sf::Event & event, Program & program)
{
	if (event.key.code != sf::Keyboard::Key::Unknown)
	{
		program.keys[event.key.code] = true;
	}
}

void handle_key_released(const sf::Event & event, Program & program)
{
	if (event.key.code != sf::Keyboard::Key::Unknown)
	{
		program.keys[event.key.code] = false;
	}
}

void handle_resize(const sf::Event & event, Program & program)
{
	sf::View v(sf::FloatRect(0, 0, event.size.width, event.size.height));
	program.window.setView(v);
	program.redraw = true;
}

//
//	Miscellaneous
//
void init_program(Program & program)
{
	program.window.create(sf::VideoMode(WIDTH, HEIGHT), TITLE, STYLE);
	program.window.setMouseCursorVisible(true);

	program.font.loadFromFile(FONT_NAME);
	program.redraw = true;
	program.update = true;
	program.running = true;

	program.state = STATE_MENU;
	program.next_state = program.state;

	for (bool & k : program.keys) k = false;
}

bool is_in(sf::Vector2f mouse, sf::Vector2f pos, sf::Vector2f size)
{
	float x0 = pos.x;
	float y0 = pos.y;
	float x1 = x0 + size.x;
	float y1 = y0 + size.y;

	if (mouse.x >= x0 && mouse.x < x1 && mouse.y >= y0 && mouse.y < y1)
		return true;
	else
		return false;
}

bool is_in(sf::Vector2f pos, const Tile & tile)
{
	float x0 = tile.rect.getPosition().x;
	float y0 = tile.rect.getPosition().y;
	float x1 = x0 + TILE_SIZE;
	float y1 = y0 + TILE_SIZE;

	if (pos.x >= x0 && pos.x < x1 && pos.y >= y0 && pos.y < y1)
		return true;
	else
		return false;
}

int dimoffset(int N, const size_t a)
{
	if (N == 0 || N == 1)
		return TILE_SIZE + 1;
	else if (N == 2)
		return a * dimoffset(0, a) + TileNOffset;
	else
		return a * dimoffset(N - 2, a) + (2) * TileNOffset;
}
