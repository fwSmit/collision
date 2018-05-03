#include <SFML/Graphics.hpp>
#include "Physics.h"
#include <iostream>

int main(){
	int caseN = 2;
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Collision");
	//window.setFramerateLimit(2);
	Physics physics(window);
	switch(caseN){
		case 0:// direct hit
			physics.addObject(arma::fvec2{100, 100}, arma::fvec2{20, 10});
			physics.addObject(arma::fvec2{160, 150}, arma::fvec2{0, 0});
			break;
		case 1:
			physics.addObject(arma::fvec2{200, 30}, arma::fvec2{-50, 10});
			physics.addObject(arma::fvec2{160, 150}, arma::fvec2{0, 0});
			break;
		case 2:// direct hit
			physics.addObject(arma::fvec2{200, 400}, arma::fvec2{-5, -100});
			physics.addObject(arma::fvec2{160, 150}, arma::fvec2{0, 0});
			break;
	}
	//physics.addLine(arma::fvec2{60, 30}, arma::fvec2{400, 1000});
	//physics.addLine(arma::fvec2{60, 30}, arma::fvec2{600, 100});
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
