#pragma once

#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <string>

namespace mdl3D
{
	class Model;
	class Space;

	struct Vertex
	{
		double x, y, z;
	};
	struct Edge
	{
		Vertex V1, V2;
	};

	class Space
	{
	public:
		Space(double x, double y, double z, int focus, int distance, int x_cam, int y_cam, int z_cam)
			: x(x), y(y), z(z), focus(focus), distance(distance), x_cam(x_cam), y_cam(y_cam), z_cam(z_cam)
		{
			//this->x += x_cam;
			//this->y += y_cam;
			//this->z += z_cam;
		}
		Space(const Space& spc)
		{
			x = spc.x; y = spc.y; z = spc.z;
			focus = spc.focus; distance = spc.distance;
			x_cam = spc.x_cam; y_cam = spc.y_cam; z_cam = spc.z_cam;
			models = spc.models;
		}
		const unsigned char id = '0';

		double x, y, z;
		int focus, distance;
		int x_cam, y_cam, z_cam;
		std::vector<Model*> models;

		void showAxes(sf::RenderWindow& window, int len = 10, Model* mdl = NULL, sf::Color color = sf::Color::Cyan);

		void rotateX(double angle);
		void rotateY(double angle);
		void rotateZ(double angle);

	};

	class Model
	{
	public:
		Model(
			std::string name,
			Space* space,
			Vertex pos,
			std::vector<Edge> edges,
			sf::Color color = sf::Color::White)
			: name(name), space(space), position(pos), edges(edges), color(color)
		{
			space->models.push_back(this);
		}
		const unsigned char id = '1';

		//вывод на экран модели
		void draw(sf::RenderWindow& window);

		//вращение по осям
		void rotateX(double angle);
		void rotateY(double angle);
		void rotateZ(double angle);

		//перемещение
		void moveX(int len);
		void moveY(int len);
		void moveZ(int len);

		// геттеры
		std::string get_name()			{ return name; }
		std::vector<Edge>* get_edges()  { return &edges; }
		Vertex* get_position()          { return &position; }
		Space* get_space()              { return space; }
		sf::Color* get_color()		    { return &color; }

		//
		void set_edges(std::vector<Edge> edgs) { edges = edgs; }
		void set_position(Vertex pos)          { position = pos; }
		void set_space(Space* sps)             { space = sps; }
		void set_color(sf::Color clr)          { color = clr; }

		//
		void update(Space* space);


	private:
		std::vector<Edge> edges;
		Vertex position;
		Space* space;
		sf::Color color;
		std::string name;
	};

	//template<class T>
	//void showAxes(sf::RenderWindow& window, T t, int len, sf::Color color) {
	//	Vertex shift = NULL;
	//	switch (t.id) {
	//	case '0':
	//		shift = { 0, 0, 0 };
	//		break;
	//	case '1':
	//		shift = { t.get_position().x, t.get_position().y, t.get_position().z };
	//		break;
	//	}
	//	
	//	sf::Vertex lineX[] = {
	//		sf::Vertex(
	//			sf::Vector2f(
	//				x + (0 + len - x_cam) * focus / distance,
	//				z + (0 + z_cam) * focus / distance
	//			),
	//			color
	//		),
	//		sf::Vertex(
	//			sf::Vector2f(
	//				x + (0 - len - x_cam) * focus / distance,
	//				z + (0 + z_cam) * focus / distance
	//			),
	//			color
	//		)
	//	};
	//	sf::Vertex lineZ[] = {
	//		sf::Vertex(
	//			sf::Vector2f(
	//				x + (0 - x_cam) * focus / distance,
	//				z + (0 + len + z_cam) * focus / distance
	//			),
	//			color
	//		),
	//		sf::Vertex(
	//			sf::Vector2f(
	//				x + (0 - x_cam) * focus / distance,
	//				z + (0 - len + z_cam) * focus / distance
	//			),
	//			color
	//		)
	//	};
	//	sf::Vertex lineY[] = {
	//		sf::Vertex(
	//			sf::Vector2f(
	//				x + (0 - x_cam) * focus / (distance + (y + len)),
	//				z + (0 + z_cam) * focus / (distance + (y + len))
	//			),
	//			color
	//		),
	//		sf::Vertex(
	//			sf::Vector2f(
	//				x + (0 - x_cam) * focus / (distance + (y - len) <= 0 ? 1 : distance + (y - len)),
	//				z + (0 + z_cam) * focus / (distance + (y - len) <= 0 ? 1 : distance + (y - len))
	//			),
	//			color
	//		)
	//	};
	//	window.draw(lineX, 2, sf::Lines);
	//	window.draw(lineZ, 2, sf::Lines);
	//	window.draw(lineY, 2, sf::Lines);
	//}

	void debug();

}



