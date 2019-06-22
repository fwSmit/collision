#include <iostream>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Physics.h"
#include "Circle.h"

int main(){
	// std::cout << "hello world" << std::endl;
	// op::createWindow(sf::VideoMode(1000, 800), "SFML Collision");
	// op::createPhysics();
	Circle circle;
	op::getPhysics().setWalls(true);
	op::getPhysics().addObject({200, 200}, {10, 400}, 30);
	op::getPhysics().addObject({300, 200}, {100, 40}, 30);
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
		op::getPhysics().draw();
		// circle.draw();
		op::getWindow().display();
	}
}
