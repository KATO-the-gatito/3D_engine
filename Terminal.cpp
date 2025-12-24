#include "Terminal.h"

int Terminal::enter() {
	std::string command;

	std::cin >> command;


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