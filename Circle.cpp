#include "Circle.h"
#include <iostream>
#include <SFML/Graphics.hpp>

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

fvec2 Circle::getVel(){
	return vel;
}

void Circle::setVel(fvec2 _vel){
	//std::cout << "new vel set to: "  << _vel << std::endl;
	vel = _vel;
}

void Circle::setPos(fvec2 _pos){
	pos = _pos;
	//cout << pos << endl;
}

float Circle::getRadius(){
	return radius;
}

float Circle::getMass(){
	return mass;
}

void Circle::travel(float time){
	pos += vel * time;
}

