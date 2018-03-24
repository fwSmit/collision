#include <SFML/Graphics.hpp>
#include "Physics.h"
#include <iostream>

int main(){
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Collision");
	//window.setFramerateLimit(2);
	Physics physics(window);
	physics.addObject(arma::fvec2{600, 30}, arma::fvec2{-400, 1000});
	sf::Clock timer;
	float deltaTime;
	while(window.isOpen()){
		deltaTime = timer.restart().asSeconds();
		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
		physics.draw(deltaTime);
        window.display();
		//std::cout << 1/deltaTime << std::endl;	
	}
}
