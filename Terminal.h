#pragma once
#include "Model.h"
#include <string>
#include <iostream>
#include <map>
#include <Windows.h>

#define COLOR_ERROR 4
#define COLOR_SUCCESS 10
#define COLOR_NORMAL 7

using byte = unsigned char;

class Terminal
{
public:
	Terminal(mdl3D::Space* space) : space(space), pen(GetStdHandle(STD_OUTPUT_HANDLE))
	{
		printf("Terminal start...\n");
	}

	int enter();
	void print_stats();

private:
	mdl3D::Space* space;
	HANDLE pen;

	std::map<std::string, byte> commands_dict {
		{"exit", 1}, {"create", 2}, {"stats", 3}, {"select", 4}
	};
	std::map<std::string, byte> commands_create_dict{
		{"type", 1}, {"name", 2}, {"color", 3}, {"colorRGB", 4}
	};
	std::map<std::string, byte> types_dict {
		{"model", 1}, {"cube", 2}
	};
	std::map<std::string, sf::Color> colors_dict {
		{"white", sf::Color::White}, {"red", sf::Color::Red}, {"green", sf::Color::Green}, {"blue", sf::Color::Blue},
		{"cyan", sf::Color::Cyan}, {"yellow", sf::Color::Yellow}, {"magenta", sf::Color::Magenta}
	};
};


