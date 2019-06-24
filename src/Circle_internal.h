#pragma once
#include <armadillo>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

class Circle_internal{
	float mass, radius;
	arma::fvec2 pos, vel;
	sf::Color fillColor = sf::Color::Blue;
public:
	//class sf::CircleShape getSfObject();
	Circle_internal();
	float getRadius();
	void setRadius(float _radius);
	float getMass();
	void setMass(float mass);
	arma::fvec2 getPos();
	void setPos(arma::fvec2 _pos);
	arma::fvec2 getVel();
	void setVel(arma::fvec2 _vel);
	void travel(float time); // moves the object by time * velocity
	void applyForce(arma::fvec2 force, float time);
	void setFillColor(sf::Color color);
	sf::Color getFillColor() const;
};
