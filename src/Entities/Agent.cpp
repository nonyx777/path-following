#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include "../../include/utility/Utility.hpp"
#include "Path.cpp"

class Agent{
    private:
        sf::Vector2f velocity, acceleration, predicted, target, normal;
        Path normal_path = Path(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), 1.f);

    public:
        sf::CircleShape agent_property;
        //.....
        Agent(const sf::Vector2f position){
            this->agent_property.setFillColor(sf::Color::White);
            this->agent_property.setRadius(1.f);
            this->agent_property.setOrigin(1.f, 1.f);
            this->agent_property.setPosition(position);

            this->velocity = sf::Vector2f(1.f, 1.f);
        };

        //main ball functions
        void update(sf::Vector2f start, sf::Vector2f end, float radius){
            this->predicted = Utility::_unitVector(this->velocity) * 5.f;
            this->predicted = this->predicted + this->agent_property.getPosition();

            sf::Vector2f path_direction = end - start;
            sf::Vector2f from_start_to_predicted = this->predicted - start;
            this->normal = Utility::_vectorProjection(from_start_to_predicted, path_direction);
            this->normal += start;

            // this->normal_path.setBase(this->agent_property.getPosition());
            // this->normal_path.setDirection(this->target);

            sf::Vector2f target_direction = Utility::_unitVector(path_direction) * 2.f;
            this->target = this->normal + target_direction;


            if(Utility::_isFar(this->normal, this->predicted, radius))
                this->steer(this->target);
            else
                this->steer(this->predicted);
        }
        void render(sf::RenderTarget* target){
            target->draw(this->agent_property);
            // this->normal_path.render(target);
        }

        //accessors and mutators
        sf::Vector2f getVelocity(){
            return this->velocity;
        }
        void setVelocity(sf::Vector2f vector){
            this->velocity = velocity;
        }

        //custom functions
        void steer(sf::Vector2f target){
            sf::Vector2f desired = target - this->agent_property.getPosition();
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
