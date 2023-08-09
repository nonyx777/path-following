#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../src/Entities/Path.cpp"
#include "../src/Entities/Agent.cpp"
#include <vector>

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
        Path path = Path(20.f);

	//agent container
	std::vector<Agent> agents;

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

	//custom functions
	void placeAgent(const sf::Vector2f position);
};
