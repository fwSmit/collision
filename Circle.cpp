#include "Circle.h"
#include <iostream>

using namespace arma;
using namespace std;

Circle::Circle(){
	mass = 1;
	radius = 30;
	pos = fvec2{0,0};
	vel = fvec2{10,10};
}

arma::fvec2 Circle::getPos(){
	return pos;
}

sf::Vector2f Circle::getSfPos(){
	return sf::Vector2f(pos[0], pos[1]);
}

fvec2 Circle::getVel(){
	return vel;
}

void Circle::setVel(fvec2 _vel){
	vel = _vel;
}

void Circle::setPos(fvec2 _pos){
	pos = _pos;
	//cout << pos << endl;
}

float Circle::getRadius(){
	return radius;
}

void Circle::travel(float time){
	pos += vel * time;
}
