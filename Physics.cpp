// credits to http://ericleong.me/research/circle-circle/#static-circle-circle-collision-response
#include "Physics.h"
#include <cmath>
#include "constants.h"

using namespace arma;

Physics::Physics(sf::RenderWindow& _window) : window(_window){
	bounds = op::toArma(window.getSize());
	lines_array.setPrimitiveType(sf::PrimitiveType::Lines);
}

void Physics::addObject(fvec2 pos, fvec2 vel){
	Circle object;
	object.setPos(pos);
	object.setVel(vel);
	objects.push_back(object);
}

void Physics::addLine(fvec2 begin, fvec2 end){
	lines.push_back(Line(begin, end));
}

void Physics::update(float deltaTime){ // known bug: 2 bound hits in one frame could cause the object to go out of bounds
	bool travelNormally = true;
	static bool once = true;
	for(auto& object : objects){
		for(auto line : lines){
			fvec2 direction = line.getDirection();
			fvec2 vel_paralel = op::getParalel(object.getVel(), direction);
			fvec2 vel_perpendicular = object.getVel() - vel_paralel;
			fvec2 p = object.getPos();
			fvec2 project_p = closestPointOnLine(line, p);
			float distance = arma::norm(p-project_p) - object.getRadius();
			//cout << distance << endl;
			cout << project_p << endl;
			float speed_perpendicular = arma::norm(vel_perpendicular);
			float hitTime = distance / speed_perpendicular;
			//cout << hitTime << endl;
			if(hitTime < deltaTime){
				travelNormally = false;
				//std::cout << "Hit" << std::endl;
				object.travel(hitTime);
				fvec2 newVel = vel_paralel - vel_perpendicular;
				object.setVel(newVel);
				object.travel(deltaTime-hitTime);
			}
		
			
			
			if(once){
				object.setVel(vel_perpendicular);
				//cout << "direction: " << direction << endl;
				//object.setVel(100* direction);
				once = false;
			}
		}
		if(object.getVel()[0] != 0 && object.getVel()[1] != 0){ // bounds detection
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
				travelNormally = false;
				if(horizontalBound < verticalBound){ // left or right
					object.travel(boundHitTime);
					auto vel = object.getVel();
					vel[0] = -vel[0]; // inverse x-component of velocit
					object.setVel(vel);
					object.travel(deltaTime-boundHitTime);
				}
				else{ // top or bottom
					object.travel(boundHitTime);
					arma::fvec2 vel = object.getVel();
					vel[1] = -vel[1]; // inverse y-component of velocity
					object.setVel(vel);
					object.travel(deltaTime-boundHitTime);
				}
			}
			if(travelNormally){
				object.travel(deltaTime);
			}
		}
	}
	if(lines.size() > 0){
		Line line = lines[0];
		arma::fvec2 p = op::toArma(sf::Mouse::getPosition(window));
		arma::fvec2 project_p = closestPointOnLine(line, p);
		op::drawPoint(p, window);
		op::drawPoint(project_p, window);
		//cout << "distance: " << std::sqrt(arma::accu(arma::pow(p - project_p, 2))) << endl;
		//cout << "end" << endl;
	}
}

void Physics::draw(float deltaTime){
	update(deltaTime);
	for(int i = 0; i < objects.size(); i++){
		sf::CircleShape circle;
		circle.setPosition(op::toSf(objects[i].getPos()));
		circle.setRadius(op::toSf(objects[i].getRadius()));
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setFillColor(sf::Color(0, 0, 255, 120));
		window.draw(circle);
	}
	lines_array.clear();
	for(int i = 0; i < lines.size(); i++){
		lines_array.append(op::toSf(lines[i].getStart()));
		lines_array.append(op::toSf(lines[i].getEnd()));
	}
	window.draw(lines_array);
}

arma::fvec2 Physics::closestPointOnLine(Line line, arma::fvec2 p){
	// line start = A and line end = B
	fvec2 AP = p - line.getStart();
	fvec2 AB = line.getEnd() - line.getStart();

	float magnitudeAB = arma::accu(arma::pow(AB, 2));
	float dotProduct = arma::dot(AP, AB);
	float distance = dotProduct / magnitudeAB; // not an actual distance

	return line.getStart() + AB * distance;

    //float a = line.getA();
	//float b = line.getB();
	//float c = line.getC();
	//float h = b*p[1]-(b*b)/a * p[0];
	//float j = (c-h)/(pow(b, 2)/a + a);
	//float k = (-a/b)*j + c/b; 
	//return arma::fvec2{j,k};
}
