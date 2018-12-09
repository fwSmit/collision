#include "Circle.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace arma;
using namespace std;

Circle::Circle(){
	setRadius(30);
	setPos(fvec2{100, 100});
	setVel( fvec2{10,10} );
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

void Circle::setRadius(float _radius){
	radius = _radius;
	setMass(4/3 * arma::datum::pi * pow( _radius, 3));
}

float Circle::getMass(){
	return mass;
}

void Circle::setMass(float _mass){
	mass = _mass;
}

void Circle::travel(float time){
	pos += vel * time;
}

void Circle::applyForce(arma::fvec2 force, float time){
	fvec2 acceleration = force / getMass();
	setVel(getVel() + acceleration * time);
}
