#include <SFML/Graphics.hpp>
#include "Model.h"

void mdl3D::Model::draw(sf::RenderWindow& window) {

	// конвертируем координаты оси y в проекцию на плоскость камеры (по умолчанию плоскость xz)

	//printf("x_cam: %d, y_cam: %d, z_cam: %d\n", space->x_cam, space->y_cam, space->z_cam);

	int focus = space->focus, distance = space->distance;

	for (Edge& edge : edges) {
		sf::Vertex line[] = {
			sf::Vertex(
				sf::Vector2f(
					space->x + (edge.V1.x + position.x - space->x_cam) * focus / (distance + position.y + edge.V1.y + space->y_cam),  // x
					space->z + (edge.V1.z - position.z + space->z_cam) * focus / (distance + position.y + edge.V1.y + space->y_cam)   // y
				),
				color
			),
			sf::Vertex(
				sf::Vector2f(
					space->x + (edge.V2.x + position.x - space->x_cam) * focus / (distance + position.y + edge.V2.y + space->y_cam),  // x
					space->z + (edge.V2.z - position.z + space->z_cam) * focus / (distance + position.y + edge.V2.y + space->y_cam)   // y
				),
				color
			)
		};
		window.draw(line, 2, sf::Lines);
	}
}
void mdl3D::Model::rotateX(double angle) {
	for (Edge& edge : edges) {
		double y1 = edge.V1.y;
		edge.V1.y = y1 * cos(angle) - edge.V1.z * sin(angle);
		edge.V1.z = y1 * sin(angle) + edge.V1.z * cos(angle);
		double y2 = edge.V2.y;
		edge.V2.y = y2 * cos(angle) - edge.V2.z * sin(angle);
		edge.V2.z = y2 * sin(angle) + edge.V2.z * cos(angle);
	}
}
void mdl3D::Model::rotateY(double angle) {
	for (Edge& edge : edges) {
		double x1 = edge.V1.x;
		edge.V1.x = x1 * cos(angle) + edge.V1.z * sin(angle);
		edge.V1.z = -x1 * sin(angle) + edge.V1.z * cos(angle);
		double x2 = edge.V2.x;
		edge.V2.x = x2 * cos(angle) + edge.V2.z * sin(angle);
		edge.V2.z = -x2 * sin(angle) + edge.V2.z * cos(angle);
	}
}
void mdl3D::Model::rotateZ(double angle) {
	for (Edge& edge : edges) {
		double x1 = edge.V1.x;
		edge.V1.x = x1 * cos(angle) - edge.V1.y * sin(angle);
		edge.V1.y = x1 * sin(angle) + edge.V1.y * cos(angle);
		double x2 = edge.V2.x;
		edge.V2.x = x2 * cos(angle) - edge.V2.y * sin(angle);
		edge.V2.y = x2 * sin(angle) + edge.V2.y * cos(angle);
	}
}

void mdl3D::Model::moveX(int len) {
	position.x += len;
}
void mdl3D::Model::moveY(int len) {
	position.y += len;
}
void mdl3D::Model::moveZ(int len) {
	position.z += len;
}

void mdl3D::Model::update(Space* spc) {
	space = spc;
}



void mdl3D::Space::showAxes(sf::RenderWindow& window, int len, Model* mdl, sf::Color color) {
	Vertex shift = !mdl ? Vertex{ 0, 0, 0 } : Vertex{ mdl->get_position()->x, mdl->get_position()->y, mdl->get_position()->z };

	sf::Vertex lineX[] = {
		sf::Vertex(
			sf::Vector2f(
				x + (0 + shift.x + len - x_cam) * focus / (distance + shift.y + y_cam),
				z + (0 - shift.z + z_cam) * focus / (distance + shift.y + y_cam)
			),
			color
		),
		sf::Vertex(
			sf::Vector2f(
				x + (0 + shift.x - len - x_cam) * focus / (distance + shift.y + y_cam),
				z + (0 - shift.z + z_cam) * focus / (distance + shift.y + y_cam)
			),
			color
		)
	};

	sf::Vertex lineZ[] = {
		sf::Vertex(
			sf::Vector2f(
				x + (0 + shift.x - x_cam)*focus / (distance + shift.y + y_cam),
				z + (0 - shift.z + len + z_cam)*focus / (distance + shift.y + y_cam)
			),
			color
		),
		sf::Vertex(
			sf::Vector2f(
				x + (0 + shift.x - x_cam)*focus / (distance + shift.y + y_cam),
				z + (0 - shift.z - len + z_cam)*focus / (distance + shift.y + y_cam)
			),
			color
		)
	};

	sf::Vertex lineY[] = {
		sf::Vertex(
			sf::Vector2f(
				x + (0 + shift.x - x_cam) * focus / (distance + shift.y + (y + len) + y_cam),
				z + (0 - shift.z + z_cam) * focus / (distance + shift.y + (y + len) + y_cam)
			),
			color
		),
		sf::Vertex(
			sf::Vector2f(
				x + (0 + shift.x - x_cam) * focus / (y_cam + shift.y + (y - len) <= 0 ? 1 : distance + shift.y + (y - len) + y_cam),
				z + (0 - shift.z + z_cam) * focus / (y_cam + shift.y + (y - len) <= 0 ? 1 : distance + shift.y + (y - len) + y_cam)
			),
			color
		)
	};

	window.draw(lineX, 2, sf::Lines);
	window.draw(lineZ, 2, sf::Lines);
	window.draw(lineY, 2, sf::Lines);
}

void mdl3D::Space::rotateX(double angle) {
	for (Model* model : models) {
		model->get_position()->y = model->get_position()->y * cos(angle) - model->get_position()->z * sin(angle);
		model->get_position()->z = model->get_position()->y * sin(angle) + model->get_position()->z * cos(angle);
		model->rotateX(-angle);
	}
}
void mdl3D::Space::rotateY(double angle) {
	for (Model* model : models) {
		model->get_position()->x = model->get_position()->x * cos(angle) + model->get_position()->z * sin(angle);
		model->get_position()->z = -model->get_position()->x * sin(angle) + model->get_position()->z * cos(angle);
		model->rotateY(-angle);
	}
}
void mdl3D::Space::rotateZ(double angle) {
	for (Model* model : models) {
		model->get_position()->x = model->get_position()->x * cos(angle) - model->get_position()->y * sin(angle);
		model->get_position()->y = model->get_position()->x * sin(angle) + model->get_position()->y * cos(angle);
		model->rotateZ(angle);
	}
}


void mdl3D::debug() {
	//printf("x: %d, y: %d, z: %d\n", zeroCoord.x, zeroCoord.y, zeroCoord.z);
	printf("fwfwf\n");
}