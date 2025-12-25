#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include "Model.h"
#include "Terminal.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 700), "SFML works!");

    mdl3D::Space space(500, 0, 100, 200, 100, 200, 0, 200); //  = { 300, 0, 300, 200, 200, 0, 0, 50 };
    Terminal terminal(&space);

    // ВАЖНО!!! координаты вершины НЕ указывают на ее расположение во всем пространстве
    
    // вершины и их координаты в системе координат модели
    mdl3D::Vertex A = { 50,-50,50 };
    mdl3D::Vertex B = { -50,-50,50 };
    mdl3D::Vertex C = { -50,50,50 };
    mdl3D::Vertex D = { 50,50,50 };
    mdl3D::Vertex A1 = { 50,-50,-50 };
    mdl3D::Vertex B1 = { -50,-50,-50 };
    mdl3D::Vertex C1 = { -50,50,-50 };
    mdl3D::Vertex D1 = { 50,50,-50 };

    mdl3D::Model cube(
        "cube 1",
        &space, // пространство, которому принадлежит модель
        { 75, 100, 50 }, // координаты модели (центр мини-системы координат, находящейся в основном пространстве)
        {
            {A, B}, {B, C}, {C, D}, {D, A},  //верхняя часть куба
            {A1, B1}, {B1, C1}, {C1, D1}, {D1, A1}, // нижняя часть куба
            {A, A1}, {B, B1}, {C, C1}, {D, D1} // связи верхних точек и нижних
        }, // все грани модели
        sf::Color(0, 255, 0) // цвет модели (необязательно)
    );
    mdl3D::Model cube2(
        "cube 2",
        &space, // пространство, которому принадлежит модель
        { 250, 100, 50 }, // координаты модели (центр мини-системы координат, находящейся в основном пространстве)
        {
            {A, B}, {B, C}, {C, D}, {D, A},  //верхняя часть куба
            {A1, B1}, {B1, C1}, {C1, D1}, {D1, A1}, // нижняя часть куба
            {A, A1}, {B, B1}, {C, C1}, {D, D1} // связи верхних точек и нижних
        }, // все грани модели
        sf::Color(255, 255, 0) // цвет модели (необязательно)
    );
    
    
    double c = 0, angle = 0.05;
    int step = 3;
    unsigned sel_model = 0;
    mdl3D::Model* selected_model = NULL;

    terminal.print_stats();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            switch (event.type) 
            {
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                // всякое остальное
                case sf::Keyboard::Numpad1:
                    sel_model = 0;
                    break;
                case sf::Keyboard::Numpad2:
                    sel_model = 1;
                    break;
                case sf::Keyboard::T:
                    terminal.enter();
                    break;
                

                // изменение параметров пространства

                // X
                case sf::Keyboard::A:
                    space.x_cam -= step;
                    break;
                case sf::Keyboard::D:
                    space.x_cam += step;
                    break;
                // Y
                case sf::Keyboard::W:
                    space.y_cam -= step;
                    break;
                case sf::Keyboard::S:
                    space.y_cam += step;
                    break;
                // Z
                case sf::Keyboard::LShift:
                    space.z_cam -= step;
                    break;
                case sf::Keyboard::Space:
                    space.z_cam += step;
                    break;
                // focus
                case sf::Keyboard::F:
                    space.focus -= step;
                    break;
                case sf::Keyboard::R:
                    space.focus += step;
                    break;
                // вращение
                case sf::Keyboard::Q:
                    space.rotateZ(angle);
                    break;
                case sf::Keyboard::E:
                    space.rotateZ(-angle);
                    break;

                // изменение параметров модели
                
                // X
                case sf::Keyboard::Left:
                    selected_model->moveX(-step);
                    break;
                case sf::Keyboard::Right:
                    selected_model->moveX(step);
                    break;
                // Y
                case sf::Keyboard::Up:
                    selected_model->moveY(step);
                    break;
                case sf::Keyboard::Down:
                    selected_model->moveY(-step);
                    break;
                // Z
                case sf::Keyboard::RShift:
                    selected_model->moveZ(step);
                    break;
                case sf::Keyboard::RControl:
                    selected_model->moveZ(-step);
                    break;
                // вращение Z
                case sf::Keyboard::Delete:
                    selected_model->rotateZ(-angle);
                    break;
                case sf::Keyboard::PageDown:
                    selected_model->rotateZ(angle);
                    break;
                // вращение Y
                case sf::Keyboard::Insert:
                    selected_model->rotateY(-angle);
                    break;
                case sf::Keyboard::PageUp:
                    selected_model->rotateY(angle);
                    break;
                // вращение X
                case sf::Keyboard::Home:
                    selected_model->rotateX(angle);
                    break;
                case sf::Keyboard::End:
                    selected_model->rotateX(-angle);
                    break;
                }
                break;
            }
        }

        switch(sel_model)
        {
        case 0:
            selected_model = &cube;
            break;
        case 1:
            selected_model = &cube2;
            break;
        default:
            selected_model = NULL;
            break;
        }

        window.clear();

        cube.draw(window);
        cube2.draw(window);
        space.showAxes(window, 1000);
        space.showAxes(window, 50, &cube, sf::Color::Red);
        space.showAxes(window, 50, &cube2, sf::Color::Red);

        //cube.rotateZ(0.05); //0.05 the best
        //space.rotateX(-0.05);

        //c++;
        //printf("%d\n", (int)c);

        

        Sleep(1);
        window.display();
    }

    return 0;
}