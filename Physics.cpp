// credits to http://ericleong.me/research/circle-circle/#static-circle-circle-collision-response
#include "Physics.h"
#include <cmath>
#include "constants.h"

using namespace arma;

Physics::Physics(sf::RenderWindow& _window) : window(_window){
	bounds = op::toArma(window.getSize());
	lines_array.setPrimitiveType(sf::PrimitiveType::Lines);

	// add the bounds
	addLine(fvec2{0, 0}, fvec2{bounds[0], 0});
	addLine(fvec2{0, 0}, fvec2{0, bounds[1]});
	addLine(fvec2{bounds[0], 0}, fvec2{bounds[0], bounds[1]});
	addLine(fvec2{0, bounds[1]}, fvec2{bounds[0], bounds[1]});
	//addLine(fvec2{10, 100}, fvec2{20, 10});
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
	static bool once = true;
	bool hasCollided = true;
	float timeLeft = deltaTime;
	Circle& circle1 = objects[0];
	Circle& circle2 = objects[1];
	Line line1 = lines[3];
	int circleID = -1;
	int lineID = -1;
	bool circleCircle;
	int count = 0;
	static bool lastFrame = false; 
	//end = true;
	bool thisFrame = sf::Mouse::isButtonPressed(sf::Mouse::Left); 
	if(lastFrame == true && thisFrame == false){
		end = false;
		cout << "next frame" << endl;
	}
	lastFrame = sf::Mouse::isButtonPressed(sf::Mouse::Left); 
	while(hasCollided && !end){
		float earliestHitTime = 100000000000;
		hasCollided = false;
		//if(objects.size() > 1){
			//for(int i = 0; i < objects.size() - 1; i++){
				//for(int j = i+1; j < objects.size(); j++){
					//Circle& u = objects[i];
					//Circle&	v = objects[j]; // v is static in reference frame
					//fvec2 u_vel = u.getVel() - v.getVel();
					//Line u_movement(u.getPos(), u.getPos() + u_vel);
					//fvec2 project_v = closestPointOnLine(u_movement, v.getPos());
					//// a_sq + b_sq = r_sq
					//float a_sq = arma::accu(arma::pow(v.getPos() - project_v, 2)); 
					//float b_sq = pow(v.getRadius() + u.getRadius(), 2) - a_sq;
					//float b = sqrt(b_sq);
					//fvec2 u_vel_unit = arma::normalise(u_vel);
					//fvec2 intersectionPoint = project_v - b*u_vel_unit;
					//float intersectionDist = arma::norm(u.getPos() - intersectionPoint);
					//float a_dist = arma::norm(u.getPos() - project_v);
					////op::drawPoint(intersectionPoint, window);
					////op::drawPoint(u.getPos(), window);
					////op::drawPoint(project_v, window);
					//bool isHitting = intersectionDist < a_dist; // when false, u is moving away from v
					//if(isHitting){
						//float hitTime = arma::norm(intersectionPoint - u.getPos())/arma::norm(u_vel);
						////cout << hitTime << endl;
						//if(hitTime  < timeLeft){
							//// not in reference frame anymore

							//if(hitTime < earliestHitTime){
								//circleCircle = true;
								//circle1 = objects[i];
								//circle2 = objects[j];
								//earliestHitTime = hitTime;
							//}
							////u.travel(hitTime);
							////v.travel(hitTime);
							////fvec2 perpendicular = u.getPos() - v.getPos();
							////fvec2 u_perp = op::getParalel(u.getVel(), perpendicular);
							////fvec2 u_paralel = u.getVel() - u_perp;
							////fvec2 v_perp = op::getParalel(v.getVel(), perpendicular);
							////fvec2 v_paralel = v.getVel() - v_perp;
							////fvec2 u_new_vel = u_paralel + v_perp;
							////fvec2 v_new_vel = v_paralel + u_perp;

							////u.setVel(u_new_vel);
							////v.setVel(v_new_vel);
							////u.travel(deltaTime - hitTime);
							////v.travel(deltaTime - hitTime);

							////travelNormally = false;


							////end = true;
							////cout << arma::norm(u.getPos() - v.getPos()) << endl;
							////vel_paralel = op::getParalel(U_vel, )
							////cout << "HIT" << endl;
						//}
					//}
					////std::cout << hitTime << endl;
					////std::cout << intersectionDist << " < " << a_dist << "? "  << std::boolalpha << (intersectionDist < a_dist)<< endl;
				//}
			//}
		//}
		int i = 0, j = 0;
		for(auto& object : objects){
			for(auto line : lines){
				fvec2 direction = line.getDirection();
				fvec2 vel_paralel = op::getParalel(object.getVel(), direction);
				fvec2 vel_perpendicular = object.getVel() - vel_paralel;
				fvec2 p = object.getPos();
				fvec2 project_p = closestPointOnLine(line, p);
				float distance = arma::norm(p-project_p) - object.getRadius();
				//cout << distance << endl;
				//cout << project_p << endl;
				float speed_perpendicular = arma::norm(vel_perpendicular);
				float hitTime = distance / speed_perpendicular;
				//cout << hitTime << endl;
				//cout << "speed perp" << speed_perpendicular << endl;
				//cout << "dist " << distance << endl; 
				//fvec2 intersectionPoint = object.getPos() + object.getVel() * hitTime;
				fvec2 intersectDir = project_p - p;
				float dir = arma::dot(arma::normalise(intersectDir), arma::normalise(object.getVel()));
				//if(j == 0){
					////op::drawPoint (intersectionPoint, sf::Color::Blue, window);
					//op::drawPoint(project_p, window);
					//cout << "direction: " << dir << endl;
				//}
				if(dir > 0){
					if(hitTime < timeLeft){
						if(hitTime < earliestHitTime){
							if(once){
								//cout << "hit time: " << hitTime << " earliest: " << earliestHitTime << endl;
								once = false;
							}
							circleCircle = false;
							circle1 = object;
							line1 = line;
							lineID = j;
							circleID = i;
							earliestHitTime = hitTime;
							//cout << "dist: " << distance << endl;
							//end = true;
						}
						//travelNormally = false;
						////std::cout << "Hit" << std::endl;
						//object.travel(hitTime);
						//fvec2 newVel = vel_paralel - vel_perpendicular;
						//object.setVel(newVel);
						//object.travel(deltaTime-hitTime);
					}
				}
				if(once){
					//object.setVel(vel_perpendicular);
					//cout << "direction: " << direction << endl;
					//object.setVel(100* direction);
					if(end){
						cout << "end" << endl;
						cout << objects[0].getPos()<< endl;
					once = false;
					}
				}
				j++;
			}
			//if(travelNormally && !end){
				//object.travel(deltaTime);
			//}
			i++;
		}
		//if(lines.size() > 0){
		//Line line = lines[0];
		//arma::fvec2 p = op::toArma(sf::Mouse::getPosition(window));
		//arma::fvec2 project_p = closestPointOnLine(line, p);
		//op::drawPoint(p, window);
		//op::drawPoint(project_p, window);
		////cout << "distance: " << std::sqrt(arma::accu(arma::pow(p - project_p, 2))) << endl;
		////cout << "end" << endl;
		//}
		if(earliestHitTime < 100000){ // there is a collision this frame
			hasCollided = true;
			//cout << earliestHitTime << endl;
			//if(circleCircle){
				////auto& u = circle1;
				////auto& v = circle2;
				//travelAll(earliestHitTime);
				//timeLeft -= earliestHitTime;
				//fvec2 perpendicular = circle1.getPos() - circle2.getPos();
				//fvec2 u_perp = op::getParalel(circle1.getVel(), perpendicular);
				//fvec2 u_paralel = circle1.getVel() - u_perp;
				//fvec2 v_perp = op::getParalel(circle2.getVel(), perpendicular);
				//fvec2 v_paralel = circle2.getVel() - v_perp;
				//fvec2 u_new_vel = u_paralel + v_perp;
				//fvec2 v_new_vel = v_paralel + u_perp;

				//circle1.setVel(u_new_vel);
				//circle2.setVel(v_new_vel);
				//cout << u_new_vel << endl;
				//cout << v_new_vel << endl;
				//cout << "circle hit" <<endl;
			//}
			//else{
				auto& object = objects[circleID];
				auto& line = lines[lineID];
				cout << "id's: " << circleID << " " << lineID << endl;
				//cout << "hitTime " << earliestHitTime << endl;
				fvec2 direction = line.getDirection();
				fvec2 vel_paralel = op::getParalel(object.getVel(), direction);
				fvec2 vel_perpendicular = object.getVel() - vel_paralel;
				fvec2 p = object.getPos();
				fvec2 project_p = closestPointOnLine(line, p);
				float distance = arma::norm(p-project_p) - object.getRadius();
				//cout << distance << endl;
				//cout << project_p << endl;
				float speed_perpendicular = arma::norm(vel_perpendicular);
				float hitTime = distance / speed_perpendicular;
				travelAll(earliestHitTime);
				timeLeft -= earliestHitTime;
				fvec2 newVel = vel_paralel - vel_perpendicular;
				object.setVel(newVel);
				cout << "line hit" << endl;
			//}
		}
		count++;
	}

	float e_k = 0;
	for(auto object : objects){ // calculate total kinetic energy
		e_k += 0.5 * pow(arma::norm(object.getVel()), 2);
	}
	
	cout << "object count: " << objects.size() << endl;
	//cout << "traveling time left" << endl;
	if(!end)
	{
		//cout << "time left" <<  timeLeft << endl; 
		travelAll(timeLeft);}
	//cout << "E_k: " << e_k << endl;
		//cout << "end of frame" << endl;
	if(count > 1)
	{cout << "This frame: " << count << endl;}
	if(once){
		//object.setVel(vel_perpendicular);
		//cout << "direction: " << direction << endl;
		//object.setVel(100* direction);
		if(end){
			cout << "end" << endl;
			cout << objects[0].getPos()<< endl;
		once = false;
		}
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
	for(int i = 4; i < lines.size(); i++){
		lines_array.append(op::toSf(lines[i].getStart()));
		lines_array.append(op::toSf(lines[i].getEnd()));
	}
	window.draw(lines_array);
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

    //float a = line.getA();
	//float b = line.getB();
	//float c = line.getC();
	//float h = b*p[1]-(b*b)/a * p[0];
	//float j = (c-h)/(pow(b, 2)/a + a);
	//float k = (-a/b)*j + c/b; 
	//return arma::fvec2{j,k};
}
