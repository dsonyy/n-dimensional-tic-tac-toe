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
	init_menu(menu);

	// Run main game loop
	while (program.running)
	{
		// States handles their input
		switch (program.state)
		{
		case STATE_GAME: handle_input_game(program, game); break;
		case STATE_MENU: handle_input_menu(program); break;
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

//
// STATE MENU
//
void init_menu(Menu & menu)
{/*
	for (int i = 1; i <= int(MAX_PLAYERS); i++)
	{
		auto pos = sf::Vector2f((i - 1) * (MENU_BUTTON_SIZE.x + 5), 30);
		Button b(font_);
		b.shape.move(pos);
		b.id = "p" + std::to_string(i);
		b.text.setString(std::to_string(i));
		b.text.setPosition(MENU_BUTTON_SIZE.x / 2 - b.text.getLocalBounds().width / 2,
			MENU_BUTTON_SIZE.y / 2 - b.text.getLocalBounds().height / 2 - 7);
		b.text.move(pos);

		b.action = [i]() { p = i; std::cout << p << std::endl; };

		buttons_.push_back(b);
	}

	for (int i = 1; i <= MAX_N; i++)
	{
		auto pos = sf::Vector2f((i - 1) * (MENU_BUTTON_SIZE.x + 5), 30 + MENU_BUTTON_SIZE.y + 20);
		Button p(font_);
		p.shape.move(pos);
		p.id = "n" + std::to_string(i);
		p.text.setString(std::to_string(i));
		p.text.setPosition(MENU_BUTTON_SIZE.x / 2 - p.text.getLocalBounds().width / 2,
			MENU_BUTTON_SIZE.y / 2 - p.text.getLocalBounds().height / 2 - 7);
		p.text.move(pos);

		p.action = [i]() { n = i; std::cout << n << std::endl; };

		buttons_.push_back(p);
	}

	for (int i = 1; i <= 12; i++)
	{
		auto pos = sf::Vector2f((i - 1) * (MENU_BUTTON_SIZE.x + 5), 30 + MENU_BUTTON_SIZE.y + 70);
		Button p(font_);
		p.shape.move(pos);
		p.id = "a" + std::to_string(i);
		p.text.setString(std::to_string(i));
		p.text.setPosition(MENU_BUTTON_SIZE.x / 2 - p.text.getLocalBounds().width / 2,
			MENU_BUTTON_SIZE.y / 2 - p.text.getLocalBounds().height / 2 - 7);
		p.text.move(pos);

		p.action = [i]() { a = i; std::cout << a << std::endl; };

		buttons_.push_back(p);
	}

	for (int i = 1; i <= 12; i++)
	{
		auto pos = sf::Vector2f((i - 1) * (MENU_BUTTON_SIZE.x + 5), 30 + MENU_BUTTON_SIZE.y + 120);
		Button p(font_);
		p.shape.move(pos);
		p.id = "r" + std::to_string(i);
		p.text.setString(std::to_string(i));
		p.text.setPosition(MENU_BUTTON_SIZE.x / 2 - p.text.getLocalBounds().width / 2,
			MENU_BUTTON_SIZE.y / 2 - p.text.getLocalBounds().height / 2 - 7);
		p.text.move(pos);

		p.action = [i]() { r = i; std::cout << r << std::endl; };

		buttons_.push_back(p);
	}

	Button p(font_);
	p.action = []() { init_game(); current_state = &state_game; };
	buttons_.push_back(p);*/

}

void handle_input_menu(Program & program)
{
	sf::Event event;

	while (program.window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed: handle_close(event, program); break;
		case sf::Event::Resized: handle_resize(event, program); break;
		case sf::Event::MouseButtonPressed:
		case sf::Event::MouseButtonReleased:
			/*for (auto & b : buttons_)
			{
				if (is_in(sf::Vector2f(sf::Mouse::getPosition(window_)), b))
				{
					b.action();
					for (auto & c : buttons_)
					{
						if (c.id[0] == b.id[0])
						c.shape.setFillColor(sf::Color::White);
					}
				b.shape.setFillColor(sf::Color::Blue);
				break;
				}
			}*/
		 case sf::Event::MouseMoved:
		 //for (auto & b : buttons_)
		 //{
		 //if (is_in(sf::Vector2f(sf::Mouse::getPosition(window_)), b))
		 //{
		 //b.text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		 //}
		 //else
		 //{
		 //b.text.setStyle(sf::Text::Bold);
		 //}
		 //}

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

	auto p = draw_menu(program, menu);
	draw_header(program, menu, p);

	program.redraw = false;

	/*
	auto color_bg = sf::Color(0, 0, 60);

	auto dialog_size = sf::Vector2f(300, 400);
	auto dialog_pos = sf::Vector2f((width_ - dialog_size.x) / 2, (height_ - dialog_size.y) / 2);
	auto color_dialog = sf::Color(255,255,255);

	window_.clear(color_bg);

	sf::RectangleShape dialog;
	dialog.setPosition(dialog_pos);
	dialog.setSize(dialog_size);
	dialog.setFillColor(color_dialog);
	dialog.setOutlineColor(sf::Color(0, 0, 0));
	dialog.setOutlineThickness(1);

	sf::RectangleShape dialog_shadow = dialog;
	dialog_shadow.move(10, 10);
	dialog_shadow.setFillColor(sf::Color(0, 0, 0));

	sf::Text txt("HYPER TIC TAC TOE", font_, 30);
	txt.setPosition(dialog_pos + sf::Vector2f(10, 10));
	txt.setFillColor(sf::Color(0, 0, 0));

	window_.draw(dialog_shadow);
	window_.draw(dialog);
	window_.draw(txt);
	for (auto & b : buttons_)
	{
		window_.draw(b.shape);
		window_.draw(b.text);
	}
	redraw_ = false;*/

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
	game.map.resize(pow(a, n), EMPTY);
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
		case sf::Event::KeyPressed:		handle_key_pressed(event, program);		break;
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
	program.window.clear(BG_COLOR);

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
	circle.setOutlineColor(BG_COLOR);
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
	value.setOutlineColor(sf::Color(0,0,20));
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
	text.setOutlineColor(BG_COLOR);
	text.setOutlineThickness(2);
	text.setStyle(sf::Text::Bold);
	text.setPosition(program.window.getSize().x  / 2 - text.getLocalBounds().width / 2, 20);

	program.window.draw(text);
}

void draw_legend(Program & program)
{ 
	auto text = sf::Text("Arrows/WASD - Move camera    Mouse Left - Select field    ESC - Show menu", program.font, FONT2_SIZE);
	text.setFillColor(TEXT2_COLOR);
	text.setOutlineColor(BG_COLOR);
	text.setOutlineThickness(2);
	text.setPosition(5, program.window.getSize().y - 18);

	program.window.draw(text);
}

sf::Vector2f draw_menu(Program & program, Menu & menu, sf::Vector2f offset)
{
	auto dialog_pos = sf::Vector2f((program.window.getSize().x - MENU_WINDOW_SIZE.x) / 2, 
		(program.window.getSize().y - MENU_WINDOW_SIZE.y) / 2);
	
	auto window = sf::RectangleShape();
	auto shadow = sf::RectangleShape();

	window.setPosition(dialog_pos);
	window.setSize(MENU_WINDOW_SIZE);
	window.setFillColor(FG_COLOR);

	shadow = window;
	shadow.move(program.window.getSize().x * 0.01, program.window.getSize().y * 0.01);
	shadow.setFillColor(sf::Color(0,0,255,150));

	program.window.draw(shadow);
	program.window.draw(window);

	return dialog_pos + sf::Vector2f(MENU_WIDGET_OFFSET.x, MENU_WIDGET_OFFSET.x) + offset;
}

sf::Vector2f draw_header(Program & program, Menu & menu, sf::Vector2f offset)
{
	auto text = sf::Text("HYPER TIC TAC TOE", program.font, 20);
	
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::White);
	text.setPosition(offset);
	text.setOutlineThickness(2);
	text.setOutlineColor(sf::Color::Black);

	program.window.draw(text);

	return offset + sf::Vector2f(0, MENU_WIDGET_OFFSET.y);
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

void init_button(Button & button, const Program & program)
{
	button.shape.setSize(MENU_BUTTON_SIZE);
	button.shape.setOutlineThickness(1);
	button.shape.setOutlineColor(sf::Color::Black);

	button.text.setFont(program.font);
	button.text.setCharacterSize(FONT_SIZE);
	button.text.setFillColor(sf::Color::Black);
	button.text.setStyle(sf::Text::Bold);
}


bool is_in(sf::Vector2f pos, const Button & button)
{
	float x0 = button.shape.getPosition().x;
	float y0 = button.shape.getPosition().y;
	float x1 = x0 + button.shape.getSize().x;
	float y1 = y0 + button.shape.getSize().y;

	if (pos.x >= x0 && pos.x < x1 && pos.y >= y0 && pos.y < y1)
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
