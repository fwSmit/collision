#include "Circle.h"

int main(){
	sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML Collision");
	Physics physics(window);
	Circle circle;
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
		physics.update(deltaTime);
		circle.draw();
		window.display();
	}
}
