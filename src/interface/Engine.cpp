#include "../../include/interface/Engine.h"

//defining initializer functions
void Engine::initVariables(){
    this->window = nullptr;
}
void Engine::initWindow(){
    this->video_mode.width = 600;
    this->video_mode.height = 300;
    this->window = new sf::RenderWindow(this->video_mode, "Path-Follow", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

//defining constructor and destructor
Engine::Engine(){
    this->initVariables();
    this->initWindow();
}
Engine::~Engine(){
    delete this->window;
}

//defining accessors
const bool Engine::running() const{
    return this->window->isOpen();
}

//defining window functions
void Engine::pollEvent(){
    while(this->window->pollEvent(this->event)){
        switch(this->event.type){
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                    this->path.setPoint(this->mouse_position_view);
                break;
        }
    }
}
void Engine::update(){
    this->pollEvent();
    this->mouse_position = sf::Mouse::getPosition(*this->window);
    this->mouse_position_view = this->window->mapPixelToCoords(this->mouse_position);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        this->placeAgent(this->mouse_position_view);

    // for(Agent &agent : this->agents)
    //     agent.update(this->path.getBase(), this->path.getDirection(), this->path.getRadius());
}
void Engine::render(){
    this->window->clear(sf::Color::Black);
    this->path.render(this->window);
    for(Agent &agent : this->agents)
	    agent.render(this->window);
    this->window->display();
}

//defining custom functions
void Engine::placeAgent(const sf::Vector2f position){
	Agent agent = Agent(position);
	this->agents.push_back(agent);
}
