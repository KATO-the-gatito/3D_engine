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

int Terminal::enter() { // create type cube 50 | color green | name supercube
	std::string command;
	std::vector<std::string> parsed_command;

	printf("\n> ");
	std::cin >> command;
	parsed_command = split(command);

	switch (commands_dict[command]) // <exit> <create>
	{
	case 1: // exit
		return 0;
	case 2: // create
		try
		{
			std::vector<mdl3D::Edge> edges;
			std::string name = "unnamed_model_";
			name += std::to_string(space->models.size() + 1);
			sf::Color color = sf::Color::White;

command_handler:
			std::string cmd;
			std::cin >> cmd;

			switch (commands_create_dict[cmd]) // <type> <name> <color> 
			{
			case 1: // type
				{
				std::string type;
				std::cin >> type;

				switch (types_dict[type]) // <model> <cube>
				{
				case 1: // model
					//...
					break;
				case 2: // cube
					{
					int size;
					std::cin >> size;

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
				break;
			case 2: // name
				{
				std::cin >> name;
				}
				break;
			case 3: // color
				{
				std::string clr;
				std::cin >> clr;
				color = colors_dict[clr];
				}
				break;
			case 4: // colorRGB
				{
				int R, G, B;
				std::cin >> R >> G >> B;
				color = sf::Color(R, G, B);
				}
				break;
			}

			std::string sep_sym;
			std::cin >> sep_sym;

			if (sep_sym == "|")
				goto command_handler;
			else if (sep_sym == "<") {
				mdl3D::Model* cube = new mdl3D::Model(
					name,
					space,
					{ 0, 0, 0 },
					edges,
					color
				);
				SetConsoleTextAttribute(pen, COLOR_SUCCESS);
				printf("model created successfully\n");
				SetConsoleTextAttribute(pen, COLOR_NORMAL);
			}
			else throw "error when creating the model\n";
		}
		catch (const char* err_message) {
			SetConsoleTextAttribute(pen, COLOR_ERROR);
			printf(err_message); //error when creating the model
			SetConsoleTextAttribute(pen, COLOR_NORMAL);
		}
		break;
	case 3:
		print_stats();
		break;
	case 4:
		try
		{
			auto it_model = space->models.begin();
			bool flag = false;
		
			std::string name;
			std::cin >> name;
		
			for (auto it = space->models.begin(); it != space->models.end(); it++) {
				if ((*it)->get_name() == name) {
					it_model = it;
					flag = true;
				}
			}
			if (flag) {
				mdl3D::Model* tmp_mdl = space->models[0];
				space->models[0] = *it_model;
				*it_model = tmp_mdl;

				SetConsoleTextAttribute(pen, COLOR_SUCCESS);
				printf("model selected\n");
				SetConsoleTextAttribute(pen, COLOR_NORMAL);
			}
			else throw "There is no model with that name\n";
		}
		catch (const char* err_message) {
			SetConsoleTextAttribute(pen, COLOR_ERROR);
			printf(err_message); 
			SetConsoleTextAttribute(pen, COLOR_NORMAL);
		}
		break;
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