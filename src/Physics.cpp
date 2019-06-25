// credits to http://ericleong.me/research/circle-circle/#static-circle-circle-collision-response
#include "Physics.h"
#include <cmath>
#include <iostream>
#include "constants.h"

using namespace arma;

Physics::Physics(){
	std::cout << sizeof(Iter_t) << std::endl;
	bounds = op::toArma(getWindow().getSize());
	createWalls();
}

Iter_t Physics::addObject(fvec2 pos, fvec2 vel){
	return addObject(pos, vel, 30);
}

Iter_t Physics::addObject(fvec2 pos, fvec2 vel, float radius){
	Circle_internal object;
	object.setPos(pos);
	object.setVel(vel);
	object.setRadius(radius);
	return addObject(object);
}

Iter_t Physics::addObject(Circle_internal object, sf::Color fillColor){
	objects.push_back(object);
	object.setFillColor(fillColor);
	return objects.end();
}

std::list<Line>::iterator Physics::addLine(fvec2 begin, fvec2 end){
	lines.push_back(Line(begin, end));
	return lines.end();
}

void Physics::update(float deltaTime){
	// this prevents crashing when there are many objects colliding in one frame. Instead of crashing the simulation will run a bit slower
	if(deltaTime > 1.f/50.f){
		deltaTime = 1.f/60.f;
	}
	static bool once = true;
	bool hasCollided = true;
	float timeLeft = deltaTime;
	Iter_t circleIt1;
	Iter_t circleIt2;
	std::list<Line>::iterator lineIt;
	bool circleCircle;
	int count = 0;
	while(hasCollided){
		float earliestHitTime = 100000000000;
		hasCollided = false;
		if(objects.size() > 1){
			for(Iter_t it1 = objects.begin(); it1 != std::prev(objects.end()); it1++){
				Iter_t it2 = it1;
				it2++;
				for(; it2 != objects.end(); it2++){
					fvec2 u_vel = it1->getVel() - it2->getVel();
					Line u_movement(it1->getPos(), it1->getPos() + u_vel);
					fvec2 project_v = closestPointOnLine(u_movement, it2->getPos());
					
					// a_sq + b_sq = r_sq
					float a_sq = arma::accu(arma::pow(it2->getPos() - project_v, 2)); 
					float b_sq = pow(it2->getRadius() + it1->getRadius(), 2) - a_sq;
					float b = sqrt(b_sq);
					fvec2 u_vel_unit = arma::normalise(u_vel);
					fvec2 intersectionPoint = project_v - b*u_vel_unit;
					float intersectionDist = arma::norm(it1->getPos() - intersectionPoint);
					float a_dist = arma::norm(it1->getPos() - project_v);
					//op::drawPoint(intersectionPoint, getWindow());
					//op::drawPoint(it1->getPos(), getWindow());
					//op::drawPoint(project_v, getWindow());
					bool isHitting = intersectionDist < a_dist; // when false, u is moving away from v
					if(isHitting){
						float hitTime = arma::norm(intersectionPoint - it1->getPos())/arma::norm(u_vel);
						if(hitTime  < timeLeft){
							if(hitTime < earliestHitTime){
								circleCircle = true;
								circleIt1 = it1;
								circleIt2 = it2;
								earliestHitTime = hitTime;
							}
						}
					}
				}
			}
		}
		for(Iter_t itObj = objects.begin(); itObj != objects.end(); itObj++){
			std::list<Line>::iterator itLine = lines.begin();
			if(!hasWalls){
				std::advance(itLine, n_walls);
			}
			for(; itLine != lines.end(); itLine++){
				fvec2 direction = (*itLine).getDirection();
				fvec2 vel_paralel = op::getParalel(itObj->getVel(), direction);
				fvec2 vel_perpendicular = itObj->getVel() - vel_paralel;
				fvec2 p = itObj->getPos();
				fvec2 project_p = closestPointOnLine(*itLine, p);
				float distance = arma::norm(p-project_p) - itObj->getRadius();
				float speed_perpendicular = arma::norm(vel_perpendicular);
				float hitTime = distance / speed_perpendicular;
				fvec2 intersectDir = project_p - p;
				float dir = arma::dot(arma::normalise(intersectDir), arma::normalise(itObj->getVel()));
				if(dir > 0){
					if(hitTime < timeLeft){
						if(hitTime < earliestHitTime){
							if(once){
								once = false;
							}
							circleCircle = false;
							lineIt = itLine;
							circleIt1 = itObj;
							earliestHitTime = hitTime;
						}
					}
				}
			}
		}
		if(earliestHitTime < 100000){ // there is a collision this frame
			hasCollided = true;
			if(circleCircle){
				travelAll(earliestHitTime);
				timeLeft -= earliestHitTime;
				fvec2 perpendicular = circleIt1->getPos() - circleIt2->getPos();
				fvec2 u_perp = op::getParalel(circleIt1->getVel(), perpendicular);
				fvec2 u_paralel = circleIt1->getVel() - u_perp;
				fvec2 v_perp = op::getParalel(circleIt2->getVel(), perpendicular);
				fvec2 v_paralel = circleIt2->getVel() - v_perp;
				fvec2 u_new_vel = (u_perp*(circleIt1->getMass() - circleIt2->getMass()) + 2*circleIt2->getMass()*v_perp)/(circleIt1->getMass() + circleIt2->getMass()) + u_paralel;
				fvec2 v_new_vel = (v_perp*(circleIt2->getMass() - circleIt1->getMass()) + 2*circleIt1->getMass()*u_perp)/(circleIt1->getMass() + circleIt2->getMass()) + v_paralel;

				circleIt1->setVel(u_new_vel);
				circleIt2->setVel(v_new_vel);
			}
			else{
				fvec2 direction = lineIt->getDirection();
				fvec2 vel_paralel = op::getParalel(circleIt1->getVel(), direction);
				fvec2 vel_perpendicular = circleIt1->getVel() - vel_paralel;
				fvec2 p = circleIt1->getPos();
				fvec2 project_p = closestPointOnLine(*lineIt, p);
				// float distance = arma::norm(p-project_p) - object.getRadius();
				// float speed_perpendicular = arma::norm(vel_perpendicular);
				// float hitTime = distance / speed_perpendicular;
				travelAll(earliestHitTime);
				timeLeft -= earliestHitTime;
				fvec2 newVel = vel_paralel - vel_perpendicular;
				circleIt1->setVel(newVel);
			}
		}
		count++;
	}

	float e_k = 0;
	for(auto object : objects){ // calculate total kinetic energy
		e_k += 0.5 * object.getMass() * pow(arma::norm(object.getVel()), 2);
	}
	// cout << "kinetic engergy: " << e_k << endl;

	travelAll(timeLeft);
}

void Physics::mouseDrag(float deltaTime){
	// static arma::fvec2 currPos;
	// static int circleIt1;
	// static bool hasStarted = false;
	// static bool missed = false;
	// if(hasStarted){
		// if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			// hasStarted = false;
		// }
		// else{
			// currPos = op::toArma( sf::Mouse::getPosition(getWindow()) );
			// fvec2 deltaPos = currPos - objects[circleIt1].getPos();
			// deltaPos *= objects[circleIt1].getMass();
			// objects[circleIt1].applyForce(deltaPos, deltaTime);
		// }
	// }
	// if(missed && !sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			// missed = false;
	// }

	// if(hasStarted)
	// {
		// lines_array.append(op::toSf(objects[circleIt1].getPos()));
		// lines_array.append(op::toSf(currPos));
	// }

	// if(!hasStarted && !missed && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		// fvec2 mousePos = op::toArma( sf::Mouse::getPosition(getWindow()) );
		// for(std::size_t i = 0; i < objects.size(); i++){
			// if(arma::norm(mousePos - objects[i].getPos()) <= objects[i].getRadius()){
				// circleIt1 = i;
				// hasStarted = true;
				// break;
			// }
		// }
		// missed = true;
	// }
}

void Physics::draw(){
	for(Iter_t it = objects.begin(); it != objects.end(); it++){
		sf::CircleShape circle;
		circle.setPosition(op::toSf(it->getPos()));
		circle.setRadius(op::toSf(it->getRadius()));
		circle.setFillColor(it->getFillColor());
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		getWindow().draw(circle);
	}
	lines_array.clear();
	for(std::list<Line>::iterator it = lines.begin(); it != lines.end(); it++){
		lines_array.append(op::toSf(it->getStart()));
		lines_array.append(op::toSf(it->getEnd()));
	}
	// mouseDrag(deltaTime);
	getWindow().draw(lines_array);
}

void Physics::travelAll(float time){
	for(auto& object : objects){
		object.travel(time);
	}
}

arma::fvec2 Physics::closestPointOnLine(Line line, arma::fvec2 p){
	// line start = A and line end = B
	fvec2 AP = p - line.getStart();
	fvec2 AB = line.getEnd() - line.getStart();

	float magnitudeAB = arma::accu(arma::pow(AB, 2));
	float dotProduct = arma::dot(AP, AB);
	float distance = dotProduct / magnitudeAB; // not an actual distance

	return line.getStart() + AB * distance;
}

void Physics::clear(){
	objects.clear();
	lines.clear();
}

void Physics::removeCircle(const Iter_t it){
	objects.erase(it);
}

void Physics::removeLine(const std::list<Line>::iterator it){
	lines.erase(it);
}

std::size_t Physics::getNumObjects(){
	return objects.size();
}

std::size_t Physics::getNumLines(){
	return lines.size();
}

void Physics::reset(){
	clear();
	createWalls();
}

sf::RenderWindow& Physics::getWindow(){
	return *op::Singleton<sf::RenderWindow>::GetInstance();
}

void Physics::setWalls(bool _hasWalls){
	hasWalls = _hasWalls;
}

void Physics::createWalls(){
	addLine(fvec2{0, 0}, fvec2{bounds[0], 0});
	addLine(fvec2{0, 0}, fvec2{0, bounds[1]});
	addLine(fvec2{bounds[0], 0}, fvec2{bounds[0], bounds[1]});
	addLine(fvec2{0, bounds[1]}, fvec2{bounds[0], bounds[1]});
}
