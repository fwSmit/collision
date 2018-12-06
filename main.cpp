#include <SFML/Graphics.hpp>
#include "TGUI/TGUI.hpp"
#include "Physics.h"
#include "constants.h"
#include <iostream>

void initObjects(Physics& physics, sf::Window& window, int caseN);
	
int main(){
	int caseN = 9;
	bool isPaused = false, placingCircle = false, leftMouseReleased = false, firstFrame = false;
	sf::Vector2f circlePos;
	float circleRadius = 30;
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Collision");
	tgui::Gui gui{window};
	//window.setFramerateLimit(2);
	Physics physics(window);
	initObjects(physics, window, caseN);

	tgui::Slider::Ptr slider = tgui::Slider::create(10, 100);
	slider->setPosition(sf::Vector2f(30, 210));
	slider->setSize(150, 20);
	slider->setValue(30);
	gui.add(slider);

	tgui::Button::Ptr button = tgui::Button::create();
	button->setPosition(10, 50);
	button->setSize(150, 50);
	button->setText("Add");
	button->connect("MouseReleased", [&](tgui::Widget::Ptr widget, const std::string& signalName){
				auto but = widget->cast<tgui::Button>();
				placingCircle = !placingCircle; 
				if(placingCircle)
				{
					but->setText("Cancel");
				}
				else{
					but->setText("Add");
				}
				firstFrame = true;
			});
	gui.add(button);
	
	tgui::Button::Ptr button2 = tgui::Button::create();
	button2->setPosition(10, 110);
	button2->setSize(150, 50);
	button2->setText("Pause");
	button2->connect("pressed", [&](tgui::Widget::Ptr widget, const std::string& signalName)
			{
				auto but = widget->cast<tgui::Button>();
				isPaused = !isPaused; 
				if(isPaused)
				{
					but->setText("Resume");
				}
				else{
					but->setText("Pause");
				}
			});
	gui.add(button2);
	sf::Clock timer;
	float deltaTime;
	while(window.isOpen()){
		deltaTime = timer.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonReleased){
				if(event.mouseButton.button == sf::Mouse::Button::Left){
					leftMouseReleased = true;
				}
			}
			gui.handleEvent(event);
		}

		window.clear();
		if(!isPaused)
		{
			physics.update(deltaTime);
		}
		physics.draw(deltaTime);
		if(placingCircle){
			circleRadius = slider->getValue();
			sf::CircleShape circle;
			circle.setPosition(circlePos);
			circle.setRadius(op::toSf( circleRadius) );
			circle.setOrigin(circle.getRadius(), circle.getRadius());
			circle.setFillColor(sf::Color(0, 0, 255, 120));
			window.draw(circle);
			if(leftMouseReleased && !firstFrame && !slider->mouseOnWidget(op::getMousePos(window))){
				std::cout << "mouse released when placing circle on pos " << op::toArma(circlePos) << std::endl;
				Circle ci;
				ci.setRadius(circleRadius);
				ci.setPos(op::toArma( circlePos ) );
				ci.setVel(arma::fvec2{100, 100});
				physics.addObject(ci);
			}
			else{
				if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					std::cout << "changing pos to " << op::toArma(circlePos) << std::endl;
					circlePos = op::getMousePos(window);
				}
			}
		}
		gui.draw();
		window.display();
		leftMouseReleased = false;
		firstFrame = false;
	}
}

void initObjects(Physics& physics, sf::Window& window, int caseN){
	switch(caseN){
		case 0:// direct hit
			physics.addObject(arma::fvec2{100, 100}, arma::fvec2{20, 10});
			physics.addObject(arma::fvec2{160, 150}, arma::fvec2{0, 0});
			break;
		case 1: // single circle
			physics.addObject(arma::fvec2{200, 50}, arma::fvec2{-50, -100});
			break;
		case 2:// direct hit
			physics.addObject(arma::fvec2{200, 300}, arma::fvec2{-5, -100});
			physics.addObject(arma::fvec2{160, 150}, arma::fvec2{0, 0});
			break;
		case 3:// test bounds
			physics.addObject(arma::fvec2{100, 300}, arma::fvec2{-50, 100});
		case 4: // test lines
			physics.addObject(arma::fvec2{300, 200}, 0.1*arma::fvec2{400, -500});
			break;
		case 5: // two moving objects
			physics.addObject(arma::fvec2{200, 300}, arma::fvec2{-5, -100});
			physics.addObject(arma::fvec2{160, 150}, arma::fvec2{50, 20});
			break;
		case 6: // ultimate stress test (with big circles)
			physics.addObject(arma::fvec2{250, 50}, arma::fvec2{-50, 150});
			physics.addObject(arma::fvec2{30, 200}, arma::fvec2{50, 300});
			physics.addObject(arma::fvec2{30, 200}, arma::fvec2{400, -500});
			physics.addObject(arma::fvec2{300, 200}, arma::fvec2{10, -500});
			physics.addObject(arma::fvec2{20, 320}, arma::fvec2{10, -10});
			physics.addObject(arma::fvec2{50, 320}, arma::fvec2{0, 0});
			physics.addObject(arma::fvec2{50, 320}, arma::fvec2{100, 0});
			physics.addObject(arma::fvec2{50, 320}, arma::fvec2{-100, 0});
			physics.addObject(arma::fvec2{50, 320}, arma::fvec2{-200, 0});
			physics.addObject(arma::fvec2{50, 320}, arma::fvec2{-500, 0});
			break;
		case 7: // four simultaneous collisions
			{
				arma::fvec2 bounds = op::toArma(window.getSize());
				arma::fvec2 middle_pos = bounds/2;
				physics.addObject(arma::fvec2{middle_pos[0]-100, middle_pos[1]}, arma::fvec2{100, 0});
				physics.addObject(arma::fvec2{middle_pos[0]+100, middle_pos[1]}, arma::fvec2{-100, 0});
				physics.addObject(arma::fvec2{middle_pos[0], middle_pos[1]-100}, arma::fvec2{0, 100});
				physics.addObject(arma::fvec2{middle_pos[0], middle_pos[1]+100}, arma::fvec2{0, -100});
				physics.addObject(middle_pos, arma::fvec2{0, 0});
			}
			break;
		case 8: // simultaneous bound collision
			physics.addObject(arma::fvec2{100, 100}, arma::fvec2{-100, -100});
			break;
		case 9: // different radius
			{
				Circle c1, c2;
				c1.setRadius(60);
				c1.setPos(arma::fvec2{100, 200});
				c2.setPos(arma::fvec2{300, 100});
				c1.setVel(arma::fvec2{100, 20});
				c2.setVel(arma::fvec2{-10, 100});
				physics.addObject(c1);
				physics.addObject(c2);
			}
			break;
		case 10: // many small circles
			{
				Circle c;
				c.setRadius(10);
				for(int i = 0; i < 5; i ++){
					for(int j = 0; j < 5; j++){
						c.setPos(arma::fvec2{30 + i *30.f, 30+ j*30.f});
						c.setVel(arma::fvec2{arma::randu<float>()*50, arma::randu<float>() * 50});
						physics.addObject(c);
					}
				}
			}
			break;

	}
}
