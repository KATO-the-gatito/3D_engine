#include "Terminal.h"

std::vector<std::string> split(std::string str, byte ch = ' ') {
	std::string glob_str;
	std::vector <std::string> v;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ch) {
			v.push_back(glob_str);
			glob_str = "";
			while (str[i + 1] == ' ') i++;
			//i--;
		}
		else {
			glob_str.push_back(str[i]);
		}
	}
	v.push_back(glob_str);
	return v;
}

int Terminal::enter() {
	std::string command;
	std::vector<std::string> parsed_command;

	printf("\n> ");
	std::cin >> command;
	parsed_command = split(command);

	switch (commands_dict[command]) 
	{
	case 1: // exit
		return 0;
	case 2: // create
	{
		std::string cmd;
		std::cin >> cmd

		switch ()
	}
	}

	return 0;

	try
	{
		switch (commands_dict[parsed_command[0]])
		{
		case 1: // exit
			return 1;
		case 2: // create [type] [name] [size] [color [R] [G] [B], [color]]
		{
			std::vector<mdl3D::Edge> edges;
			sf::Color color;

			try
			{
				if (parsed_command[4] == "color")
					color = sf::Color(std::stoi(parsed_command[5]), std::stoi(parsed_command[6]), std::stoi(parsed_command[7]));
				else if (parsed_command.size() <= 4)
					color = sf::Color::White;
				else
					color = colors_dict[parsed_command[4]];
			}
			catch (...) {
				throw 1;
			}

			try
			{
				switch (types_dict[parsed_command[1]])
				{
				case 1: // model
					break;
				case 2: // cube
				{
					int size = std::stoi(parsed_command[3]);
					mdl3D::Vertex A = { size,-size,size };
					mdl3D::Vertex B = { -size,-size,size };
					mdl3D::Vertex C = { -size,size,size };
					mdl3D::Vertex D = { size,size,size };
					mdl3D::Vertex A1 = { size,-size,-size };
					mdl3D::Vertex B1 = { -size,-size,-size };
					mdl3D::Vertex C1 = { -size,size,-size };
					mdl3D::Vertex D1 = { size,size,-size };

					edges = std::vector<mdl3D::Edge>(
						{
							{A, B}, {B, C}, {C, D}, {D, A},
							{A1, B1}, {B1, C1}, {C1, D1}, {D1, A1},
							{A, A1}, {B, B1}, {C, C1}, {D, D1}
						}
					);
				}
				break;
				}
			}
			catch (...) {
				throw 2;
			}

			mdl3D::Model* cube = new mdl3D::Model(
				parsed_command[2],
				space,
				{ 0, 0, 0 },
				edges,
				color
			);
		}
		break;
		default:
			break;
		}
	}
	catch (int err_code) {
		switch (err_code) 
		{
		case 1:
			perror("wrong color");
			return err_code;
		case 2:
			perror("wrong type of model");
			return err_code;
		}
	}
	return 0;
}
void Terminal::print_stats() {
	printf(
		"\n---------------<Statistics>---------------\n"
		"Space: x: %d, y: %d, z: %d\n"
		"       focus: %d\n"
		"       x_cam: %d, y_cam: %d, z_cam: %d\n"
		"       count of models: %d\n"
		,
		(int)space->x, (int)space->y, (int)space->z,
		space->focus,
		space->x_cam, space->y_cam, space->z_cam,
		space->models.size()
	);
	if (space->models.size()) {
		for (mdl3D::Model* model : space->models) {
			printf(
				"Model \"%s\":\n"
				"      x: %d, y: %d, z: %d\n"
				"      count of edges: %d\n"
				"      count of vertexes: %d\n"
				"      color (RGB): (%d, %d, %d)\n"
				,
				model->get_name().c_str(),
				(int)model->get_position()->x, (int)model->get_position()->y, (int)model->get_position()->z,
				model->get_edges()->size(),
				model->get_edges()->size() * 2,
				model->get_color()->r, model->get_color()->g, model->get_color()->b
			);
		}
	}
	printf("-------------------------------------------\n");

}