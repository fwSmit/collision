#include "Physics.h"

using namespace arma;

Physics::Physics(sf::RenderWindow& _window) : window(_window){
	bounds[0] = window.getSize().x;
	bounds[1] = window.getSize().y;
}

void Physics::addObject(fvec2 pos, fvec2 vel){
	sf::CircleShape circle;
	Circle object;
	circle.setRadius(object.getRadius());
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	object.setPos(pos);
	object.setVel(vel);
	objects.push_back(object);
	circles.push_back(circle);
}

void Physics::update(float deltaTime){ // known bug: 2 bound hits in one frame could cause the object to go out of bounds
	if(!end){
	for(auto& object : objects){
		// assumes the circle is in bounds
		float horizontalBound 	= object.getVel()[0] > 0 ? 	(bounds[0] - object.getPos()[0] - object.getRadius()) / object.getVel()[0] :
												(object.getPos()[0] - object.getRadius()) / - object.getVel()[0];
		float verticalBound 	= object.getVel()[1] > 0 ? 	(bounds[1] - object.getPos()[1] - object.getRadius()) / object.getVel()[1] :
													(object.getPos()[1] - object.getRadius()) / - object.getVel()[1];
		float boundHitTime = std::min(horizontalBound, verticalBound);
		//std::cout << boundHitTime << endl;
		
		if(boundHitTime < 0){
			cout << "object is probably out of bounds " << endl;
		}
		if(boundHitTime < deltaTime){
			if(horizontalBound < verticalBound){ // left or right
				object.travel(boundHitTime);
				auto vel = object.getVel();
				vel[0] = -vel[0]; // inverse x-component of velocit
				object.setVel(vel);
				object.travel(deltaTime-boundHitTime);
			}
			else{ // top or bottom
				object.travel(boundHitTime);
				auto vel = object.getVel();
				vel[1] = -vel[1]; // inverse y-component of velocity
				object.setVel(vel);
				object.travel(deltaTime-boundHitTime);
			}
			//end = true;
		}
		else{
			object.travel(deltaTime);
		}
	}
	}
}

void Physics::draw(float deltaTime){
	update(deltaTime);
	for(int i = 0; i < objects.size(); i++){
		circles[i].setPosition(objects[i].getSfPos());
		window.draw(circles[i]);
	}
}
