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
//	CONSTANTS
//
/// WINDOW

//
//	GLOBALS
//  oh noooo....
//
/// ENGINE
sf::RenderWindow window_;
sf::Vector2f mouse_pos_;
bool running_ = true;
bool redraw_ = true;
sf::Clock clock_;
sf::Time next_tick_ = clock_.getElapsedTime();
bool keys_[sf::Keyboard::KeyCount];
sf::Font font_;
size_t width_ = WIDTH;
size_t height_ = HEIGHT;

/// GAMEPLAY
Field turn_;
Map map_;

extern size_t n;
extern size_t a;
extern size_t r;

sf::Vector2f tiles_offset_ = sf::Vector2f(20,10);
float tiles_scale_ = 0;

std::vector<Tile> tiles_;

struct Button
{
	typedef std::string ID;

	ID id;
	sf::RectangleShape shape;
	sf::Text text;
	std::function<void()> action;
};

std::vector<Button> buttons_;

//
//	HEADERS
//
void init_sfml();

void init_game();
void handle_input_game();
void update_game();
void redraw_game();

bool is_in(sf::Vector2f pos, const Tile & tile);

void init_menu();
void update_menu();
void redraw_menu();
void handle_input_menu();


State state_menu =
{
	"menu",
	init_menu,
	update_menu,
	redraw_menu,
	handle_input_menu,
};

State state_game =
{
	"game",
	init_game,
	update_game,
	redraw_game,
	handle_input_game,
};

State * const current_state = &state_game;




void init_menu()
{
	Button sbutton;
	sbutton.shape.setSize(sf::Vector2f(30,30));
	sbutton.shape.setOutlineThickness(1);
	sbutton.shape.setOutlineColor(sf::Color(0, 0, 0));
	
	auto dialog_size = sf::Vector2f(300, 400);
	auto dialog_pos = sf::Vector2f((width_ - dialog_size.x) / 2, (height_ - dialog_size.y) / 2);

	sbutton.shape.setPosition(dialog_pos + sf::Vector2f(10, 30));
	sbutton.id = "test";
	buttons_.push_back(sbutton);
}

void update_menu()
{

}


void redraw_menu()
{
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
	}
	redraw_ = false;

}


bool is_in2(sf::Vector2f pos, const Button & button)
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

void handle_input_menu()
{
	sf::Event event;

	while (window_.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			running_ = false;
			break;
		case sf::Event::MouseButtonPressed:
			break;
		case sf::Event::MouseButtonReleased:
		case sf::Event::MouseMoved:
			for (auto & b : buttons_)
			{
				if (is_in2(sf::Vector2f(sf::Mouse::getPosition(window_)), b))
				{
					b.shape.setFillColor(sf::Color(100, 100, 100));
				}
				else
				{
					b.shape.setFillColor(sf::Color(255,255,255));
				}
			}

			redraw_ = true;
			break;
		case sf::Event::Resized:
			width_ = event.size.width;
			height_ = event.size.height;
			sf::View v(sf::FloatRect(0, 0, event.size.width, event.size.height));
			window_.setView(v);
			redraw_ = true;
		}
	}

}






int main(int argc, char ** argv)
{
	init_sfml();
	current_state->init();

	while (running_)
	{
		current_state->handle_input();

		if (clock_.getElapsedTime() >= next_tick_)
		{
			current_state->update();
			
			next_tick_ += sf::milliseconds(1000 / FRAME_RATE);
		}
		
		if (redraw_)
		{
			current_state->redraw();
			window_.display();
		}
	}

	return 0;
}

void init_sfml()
{
	window_.create(sf::VideoMode(WIDTH, HEIGHT), TITLE, STYLE);
	window_.setMouseCursorVisible(true);
	font_.loadFromFile("cour.ttf");
}

int f(int N)
{
	return ++N % 2 ? int(N / 2) : N / 2 - 1;
}

int dimoffset(int N)
{
	if (N == 0 || N == 1)
		return TILE_SIZE + 1;
	else if (N == 2)
		return a * dimoffset(0) + TileNOffset;
	else
		return a * dimoffset(N - 2) + (2) * TileNOffset;
}

void init_game()
{
	map_.resize(pow(a, n), EMPTY);
	turn_ = O;

	for (size_t i = 0; i < map_.size(); i++)
	{
		VMapPos v = pos_to_vector(i);
		int x = 0, y = 0;
		sf::Color color = sf::Color::White;
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
		sf::RectangleShape rect(sf::Vector2f(TILE_SIZE, TILE_SIZE));
		rect.setFillColor(color);
		rect.setPosition(x, y);

		tiles_.push_back({ i, rect, pos_to_vector(i) });

	}
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

void handle_input_game()
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
			if (event.key.code != sf::Keyboard::Key::Unknown)
			{
				keys_[event.key.code] = true;
			}
			break;
		case sf::Event::KeyReleased:
			if (event.key.code != sf::Keyboard::Key::Unknown)
			{
				keys_[event.key.code] = false;
			}
			break;
		case sf::Event::MouseButtonPressed:
			for (auto & t : tiles_)
			{
				if (is_in(mouse_pos_ - tiles_offset_, t))
				{
					t.rect.setFillColor(sf::Color(100, 100, 100));
					if (map_[t.i] == EMPTY)
					{
						map_[t.i] = turn_;
						turn_ = Field(!turn_);
						auto win = check_win(map_, t.i);
						switch (win)
						{
						case O:
							std::cout << "Player Red created a line!" << std::endl;
							break;
						case X:
							std::cout << "Player Blue created a line!" << std::endl;
							break;
						}
					}
				}
				else
				{
					t.rect.setFillColor(sf::Color::White);
				}

			}
			redraw_ = true;

			break;

		case sf::Event::MouseButtonReleased:
		case sf::Event::MouseMoved:
			mouse_pos_ = sf::Vector2f(sf::Mouse::getPosition(window_));
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				for (auto & t : tiles_)
				{
					if (is_in(mouse_pos_ - tiles_offset_, t))
					{
						t.rect.setFillColor(sf::Color(200, 200, 200));
					}
					else
					{
						t.rect.setFillColor(sf::Color::White);
					}

				}
				redraw_ = true;
			}
			break;
		case sf::Event::Resized:
			sf::View v(sf::FloatRect(0, 0, event.size.width, event.size.height));
			window_.setView(v);
			redraw_ = true;
		}
	}
}

void update_game()
{
	if (keys_[sf::Keyboard::Up] == true || keys_[sf::Keyboard::W] == true)
	{
		tiles_offset_.y += MOVE_SPEED;
		redraw_ = true;
	}
	if (keys_[sf::Keyboard::Down] == true || keys_[sf::Keyboard::S] == true)
	{
		tiles_offset_.y -= MOVE_SPEED;
		redraw_ = true;
	}
	if (keys_[sf::Keyboard::Left] == true || keys_[sf::Keyboard::A] == true)
	{
		tiles_offset_.x += MOVE_SPEED;
		redraw_ = true;
	}
	if (keys_[sf::Keyboard::Right] == true || keys_[sf::Keyboard::D] == true)
	{
		tiles_offset_.x -= MOVE_SPEED;
		redraw_ = true;
	}

	/*
	if (window_.hasFocus())
	{
		if (mouse_pos_.x < 5)
		{
			tiles_offset_.x += 1;
			redraw_ = true;
		}
		else if (mouse_pos_.x > window_.getSize().x - 5)
		{
			tiles_offset_.x -= 1;
			redraw_ = true;
		}

		if (mouse_pos_.y < 5)
		{
			tiles_offset_.y += 1;
			redraw_ = true;
		}
		else if (mouse_pos_.y > window_.getSize().y - 5)
		{
			tiles_offset_.y -= 1;
			redraw_ = true;
		}
	}
	*/
}


void redraw_game()
{
	window_.clear(BG_COLOR);

	draw_map(window_, map_, tiles_);
	draw_turn(window_, turn_);
	draw_coords(window_, pos_to_vector(10));
	draw_legend(window_);

	redraw_ = false;
}

void draw_map(sf::RenderWindow & window, const Map & map, const std::vector<Tile> & tiles)
{
	auto circle = sf::CircleShape(TILE_SIZE / 2 - 1);
	
	for (int i = 0; i < tiles.size(); i++)
	{
		auto rect = tiles[i].rect;
		rect.move(tiles_offset_);
		window.draw(rect);


		circle.setPosition(rect.getPosition() + sf::Vector2f(1, 1));
		switch (map[tiles[i].i])
		{
		case O:
		{
			circle.setFillColor(O_COLOR);
			window.draw(circle);
			break;
		}
		case X:
		{
			circle.setFillColor(X_COLOR);
			window.draw(circle);
			break;
		}
		case Y:
		{
			circle.setFillColor(Y_COLOR);
			window.draw(circle);
			break;
		}
		case Z:
		{
			circle.setFillColor(Z_COLOR);
			window.draw(circle);
			break;
		}
		}
	}
}

void draw_turn(sf::RenderWindow & window, Field turn)
{
	auto circle = sf::CircleShape(15);
	circle.setPosition(sf::Vector2f(window.getSize().x - 62, 20));
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

	window.draw(circle);
}

void draw_coords(sf::RenderWindow & window, VMapPos vpos)
{
	auto value = sf::Text();
	value.setCharacterSize(18);
	value.setFont(font_);
	value.setPosition(window.getSize().x - 40,  40);
	value.setFillColor(TEXT_COLOR);
	value.setOutlineColor(sf::Color(0,0,20));
	value.setStyle(sf::Text::Bold);
	value.setOutlineThickness(3);

	auto dim = value;
	dim.setFillColor(TEXT2_COLOR);
	dim.move(-25, 0);


	for (int i = 0; i < n; i++)
	{
		dim.setString(std::to_string(i + 1) + ": ");
		value.setString(std::to_string(vpos[i]));
		dim.move(0, 20);
		value.move(0, 20);
		window.draw(value);
		window.draw(dim);
	}
}

void draw_dialog(sf::RenderWindow & window, std::string str, sf::Color color)
{
	auto text = sf::Text(str, font_, 18);
	text.setFillColor(color);
	text.setOutlineColor(BG_COLOR);
	text.setOutlineThickness(2);
	text.setStyle(sf::Text::Bold);
	text.setPosition(window.getSize().x  / 2 - text.getLocalBounds().width / 2, 20);

	window.draw(text);
}

void draw_legend(sf::RenderWindow & window)
{ 
	auto text = sf::Text("Arrows/WASD - Move camera    Mouse Left - Select field", font_, 12);
	text.setFillColor(TEXT2_COLOR);
	text.setOutlineColor(BG_COLOR);
	text.setOutlineThickness(2);
	text.setPosition(5, window.getSize().y - 18);

	window.draw(text);
}
