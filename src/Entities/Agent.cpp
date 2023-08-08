#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>

class Agent{
    private:
        sf::Vector2f velocity, acceleration;

    public:
        sf::CircleShape agent_property;
        //.....
        Agent(const sf::Vector2f position){
            this->agent_property.setFillColor(sf::Color::White);
            this->agent_property.setRadius(1.f);
            this->agent_property.setOrigin(1.f, 1.f);
            this->agent_property.setPosition(position);
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
            //desired = Utility::_unitVector(desired);
            desired *= 5.f;

            sf::Vector2f steer = desired - this->velocity;

            //integration
            this->acceleration = steer * 0.05f;
            this->velocity += this->acceleration;
            this->agent_property.move(this->velocity * 0.5f);

            this->acceleration = sf::Vector2f(0.f, 0.f);
        }
};
