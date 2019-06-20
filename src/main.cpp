#include "Circle.h"
#include "constants.h"
#include "Physics.h"

int main(){
	op::createWindow(sf::VideoMode(1000, 800), "SFML Collision");
	op::createPhysics();
	Circle circle;
	sf::Clock timer;
	float deltaTime;
	while(op::getWindow().isOpen()){
		deltaTime = timer.restart().asSeconds();
		sf::Event event;
		while (op::getWindow().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				op::getWindow().close();
		}

		op::getWindow().clear();
		op::getPhysics().update(deltaTime);
		// circle.draw();
		op::getWindow().display();
	}
}
