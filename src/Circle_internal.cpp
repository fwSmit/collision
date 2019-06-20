#include "Circle_internal.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace arma;
using namespace std;

Circle_internal::Circle_internal(){
	setRadius(30);
	setPos(fvec2{100, 100});
	setVel( fvec2{10,10} );
}

arma::fvec2 Circle_internal::getPos(){
	return pos;
}

fvec2 Circle_internal::getVel(){
	return vel;
}

void Circle_internal::setVel(fvec2 _vel){
	//std::cout << "new vel set to: "  << _vel << std::endl;
	vel = _vel;
}

void Circle_internal::setPos(fvec2 _pos){
	pos = _pos;
	//cout << pos << endl;
}

float Circle_internal::getRadius(){
	return radius;
}

void Circle_internal::setRadius(float _radius){
	radius = _radius;
	setMass(4/3 * arma::datum::pi * pow( _radius, 3));
}

float Circle_internal::getMass(){
	return mass;
}

void Circle_internal::setMass(float _mass){
	mass = _mass;
}

void Circle_internal::travel(float time){
	pos += vel * time;
}

void Circle_internal::applyForce(arma::fvec2 force, float time){
	fvec2 acceleration = force / getMass();
	setVel(getVel() + acceleration * time);
}
