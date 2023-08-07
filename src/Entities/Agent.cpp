#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include "../../include/cell/Cell.hpp"
#include "../../include/utility/Utility.hpp"

class Agent{
    private:
        sf::Vector2f velocity, acceleration;

    public:
        sf::CircleShape agent_property;
        //constructor
        Agent(){
            this->agent_property.setFillColor(sf::Color::White);
            this->agent_property.setRadius(1.f);
            this->agent_property.setOrigin(10.f, 10.f);
            this->agent_property.setPosition(600.f/2.f, 600.f/2.f);
        };

        //main ball functions
        void update(){
        	//...
        }
        void render(sf::RenderTarget* target){
            target->draw(this->agent_property);
        }

        //accessors and mutators
        sf::Vector2f getVelocity(){
            return this->velocity;
        }
        void setVelocity(sf::Vector2f vector){
            this->velocity = velocity;
        }

        //custom functions
        void steer(sf::Vector2f desired){
            desired = Utility::_unitVector(desired);
            desired *= 5.f;

            sf::Vector2f steer = desired - this->velocity;

            //integration
            this->acceleration = steer * 0.05f;
            this->velocity += this->acceleration;
            this->agent_property.move(this->velocity * 0.5f);

            this->acceleration = sf::Vector2f(0.f, 0.f);
        }
};
