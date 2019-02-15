#pragma once
#include <functional>
#include <string>

struct State
{
	typedef std::string ID;

	ID id;
	std::function<void()> init;
	std::function<void()> update;
	std::function<void()> redraw;
	std::function<void()> handle_input;
};


void draw_turn(Field turn);