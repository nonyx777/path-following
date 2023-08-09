#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include "../../include/utility/Utility.hpp"
#include "Path.cpp"

class Agent{
    private:
        sf::Vector2f velocity, acceleration, predicted, target, normal;

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
        void update(std::vector<sf::Vector2f> &points, float radius){
            if(points.size() < 2)
                return;

            float max_distance_normal{100000};
            sf::Vector2f path_direction = sf::Vector2f(0.f, 0.f);

            for(int i = 0; i < points.size()-1; i++){
                sf::Vector2f path_start = points[i];
                sf::Vector2f path_end = points[i+1];

                this->predicted = Utility::_unitVector(this->velocity) * 5.f;
                this->predicted = this->predicted + this->agent_property.getPosition();

                path_direction = path_end - path_start;
                sf::Vector2f from_start_to_predicted = this->predicted - path_start;
                this->normal = Utility::_vectorProjection(from_start_to_predicted, path_direction);

                //checking if normal point in on the path
                // if(this->normal.x < path_start.x)
                //     this->normal = path_start;
                if(this->normal.x > path_end.x)
                    this->normal = path_end;
                //check which normal point is the closest
                float distance_normal = Utility::_magnitude(Utility::_displacement(this->predicted, this->normal));
                if(distance_normal < max_distance_normal){
                    max_distance_normal = distance_normal;
                    this->normal += path_start;
                    this->target = this->normal;
                }
            }
            // sf::Vector2f target_direction = Utility::_unitVector(path_direction) * 2.f;

            if(Utility::_isFar(this->normal, this->predicted, radius))
                // this->agent_property.move(this->target - this->agent_property.getPosition());
                this->steer(this->target);
            else
                // this->agent_property.move(this->predicted - this->agent_property.getPosition());
                this->steer(this->predicted);
        }
        void render(sf::RenderTarget* target){
            target->draw(this->agent_property);
            // sf::Vertex normal_line[] = {
            //     this->agent_property.getPosition(),
            //     this->target
            // };
            // normal_line->color = sf::Color(sf::Color::Green);
            // target->draw(normal_line, 2, sf::Lines);
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
