#include <SFML/Graphics.hpp>

class Path{
	private:
		sf::Vector2f base;
		sf::Vector2f direction;
	public:
		Path(const sf::Vector2f base, const sf::Vector2f direction){
			this->base = base;
			this->direction = direction;
		}
		
		//main function
		void render(sf::RenderTarget* target){
			sf::Vertex path[] = {
				this->getBase(),
				this->getDirection()
			};
			target->draw(path, 2, sf::Lines);
		}

		//defining accessors and mutators
		void setBase(sf::Vector2f base){
			this->base = base;
		}
		void setDirection(sf::Vector2f direction){
			this->direction = direction;
		}
		sf::Vector2f getBase() const {
			return this->base;
		}
		sf::Vector2f getDirection() const{
			return this->direction;
		}
};
