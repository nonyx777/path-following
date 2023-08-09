#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Path{
	private:
		std::vector<sf::Vector2f> points;
		float radius;
	public:
		Path(const float radius){
			this->radius = radius;
		}
		
		//main function
		void render(sf::RenderTarget* target){
			if(this->points.size() < 2)
				return;

			for(int i = 0; i < this->points.size()-1; i++){
				sf::Vertex path[] = {
					this->points[i],
					this->points[i+1]
				};
				target->draw(path, 2, sf::Lines);
			}
		}

		//defining accessors and mutators
		void setPoint(sf::Vector2f point){
			this->points.push_back(point);
		}
		void setRadius(float radius){
			this->radius = radius;
		}
		float getRadius() const{
			return this->radius;
		}
};
