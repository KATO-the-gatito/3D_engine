#pragma once
#include "Model.h"
#include <string>
#include <iostream>
#include <map>

using byte = unsigned char;

class Terminal
{
public:
	Terminal(mdl3D::Space* space) : space(space)
	{
		printf("Terminal start...\n");
	}

	int enter();
	void print_stats();

private:
	mdl3D::Space* space;
	std::map<std::string, byte> commands_dict {
		{"exit", 1}, {"create", 2}
	};
	std::map<std::string, byte> commands_create_dict{
		{"type", 1}, {"name", 2}, {"color", 3}
	};
	std::map<std::string, byte> types_dict {
		{"model", 1}, {"cube", 2}
	};
	std::map<std::string, sf::Color> colors_dict {
		{"white", sf::Color::White}, {"red", sf::Color::Red}, {"green", sf::Color::Green}, {"blue", sf::Color::Blue}
	};
};


