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
	static bool oneFrame = false;
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		//end = false;
		//oneFrame = true;
	}
	if(!end){
		// dynamic - static circles hit detection
		if(objects.size() == 2){
			auto u = objects[0], v = objects[1]; // u is the moving circle, v is the static circle
			Line k(u.getPos(), u.getPos()+u.getVel());
			arma::fvec2 p = closestPointOnLine(k, v.getPos());
			float closestDistSq = arma::accu(arma::pow(p - v.getPos(), 2));
			float radiusSumSq = std::pow(u.getRadius() + v.getRadius(), 2);
			//cout << "dist: " << closestDistSq << endl;
			//cout << "radius: " << u.getRadius() + v.getRadius() << endl;
			//cout << "square radius: " << radiusSumSq << endl;
			bool willHit = radiusSumSq > closestDistSq;
			//cout << "willHit: " << std::boolalpha << willHit << endl;
			op::drawPoint(u.getPos(), sf::Color::Green, window);
			if(willHit){
				arma::fvec2 deltaPos = p - u.getPos();
				//if(std::signbit(deltaPos[0]) != std::signbit(u.getVel()[0])) cout << "first sign different " << endl;
				//if(std::signbit(deltaPos[1]) != std::signbit(u.getVel()[1])) cout << "second sign different " << endl;
				float backDist = std::sqrt(radiusSumSq - closestDistSq);
				arma::fvec2 pointOfCollision = p - backDist * arma::normalise(u.getVel());
				float colDistSq = arma::accu(arma::pow(u.getPos() - pointOfCollision, 2));
				float speedDtSq = arma::accu(arma::pow(u.getVel() * deltaTime, 2));
				op::drawPoint(pointOfCollision, sf::Color::White, window);
				op::drawPoint(u.getPos(), sf::Color::Yellow, window);
				float colDist = sqrt(colDistSq), speed = sqrt(arma::accu(arma::pow(u.getVel(), 2)));
				float hitTime = sqrt(colDistSq) / speed;
				//cout << "colDist :" << colDist << " speed: " << speed << endl;
				cout << "hit time: " << hitTime << endl;
				if(colDistSq < speedDtSq){
					// response
					cout << "HIT!" << endl;
					end = true;
					arma::fvec2 
						oldVel_u = u.getVel(), 
						oldVel_v = v.getVel(),
						delta = u.getPos() - v.getPos(),
						paralel_u = op::getParalel(u.getVel(), -delta),
						paralel_v = op::getParalel(v.getVel(), delta),
						perpendicular_u = u.getVel() - paralel_u,
						perpendicular_v = v.getVel() - paralel_v,
						newVel_u = (paralel_u * (u.getMass() - v.getMass()) + (2 * v.getMass() * paralel_v)) / (u.getMass() + v.getMass());
					newVel_u = arma::fvec2{10, -10};
					u.setVel(newVel_u);
					cout << u.getVel() << endl;
					//arma::fvec2 q = (2 * dot(u.getVel(), norm))/(
				}
			}
		}
	for(auto& object : objects){
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
				//end = true;
			}
			else{
				if(!end || oneFrame)
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
		cout << "distance: " << std::sqrt(arma::accu(arma::pow(p - project_p, 2))) << endl;
		cout << "end" << endl;
	}
	}	// !end
	if(oneFrame) end = true;
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
	float a = line.getA();
	float b = line.getB();
	float c = line.getC();
	float h = b*p[1]-(b*b)/a * p[0];
	float j = (c-h)/(pow(b, 2)/a + a);
	float k = (-a/b)*j + c/b; 
	return arma::fvec2{j,k};
}
