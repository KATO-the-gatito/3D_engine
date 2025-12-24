#pragma once
#include "Model.h"
#include <string>
#include <iostream>

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
};


