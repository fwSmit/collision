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
			physics.addObject(arma::fvec2{200, 300}, arma::fvec2{-5, -100});
			physics.addObject(arma::fvec2{160, 150}, arma::fvec2{0, 0});
			break;
		case 3:// test bounds
			physics.addObject(arma::fvec2{100, 300}, arma::fvec2{-50, 100});
		case 4: // test lines
			//physics.addLine(arma::fvec2{100, 300}, arma::fvec2{300, 200});
			//physics.addLine(arma::fvec2{0, 400}, arma::fvec2{900, 100});
			//physics.addLine(arma::fvec2{200, 300}, arma::fvec2{900, 300});
			physics.addObject(arma::fvec2{250, 50}, arma::fvec2{-50, 150});
			physics.addObject(arma::fvec2{30, 200}, arma::fvec2{50, 300});
			physics.addObject(arma::fvec2{30, 200}, arma::fvec2{400, -500});
			//physics.addObject(arma::fvec2{400, 600}, 40*arma::fvec2{-400, -500});
		case 5: // two moving objects
			physics.addObject(arma::fvec2{200, 300}, arma::fvec2{-5, -100});
			physics.addObject(arma::fvec2{160, 150}, arma::fvec2{50, 20});
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
		case 7: // four simultaneous collisions
			arma::fvec2 middle_pos{200, 200};
			physics.addObject(arma::fvec2{middle_pos[0]-100, middle_pos[1]}, arma::fvec2{100, 0});
			physics.addObject(arma::fvec2{middle_pos[0]+100, middle_pos[1]}, arma::fvec2{-100, 0});
			physics.addObject(arma::fvec2{middle_pos[0], middle_pos[1]-100}, arma::fvec2{0, 100});
			physics.addObject(arma::fvec2{middle_pos[0], middle_pos[1]+100}, arma::fvec2{0, -100});
			physics.addObject(middle_pos, arma::fvec2{0, 0});


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
