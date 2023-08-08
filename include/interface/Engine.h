#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../src/Entities/Path.cpp"

using namespace std;

class Engine{
    private:
        //initializer functions
        void initVariables();
        void initWindow();

        //window variables
        sf::RenderWindow* window;
        sf::VideoMode video_mode;
        sf::Event event;

        //instantiating objects
        Path path = Path(sf::Vector2f(100.f, 150.f), sf::Vector2f(500.f, 150.f), 20.f);

        //mouse position
        sf::Vector2i mouse_position;
        sf::Vector2f mouse_position_view;

    public:
        //constructor and destructor
        Engine();
        ~Engine();

        //window functions
        void pollEvent();
        void update();
        void render();

        //Accessors
        const bool running() const;
};
