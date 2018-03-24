#include <armadillo>
#include <SFML/System/Vector2.hpp>

class Circle{
	float mass, radius;
	arma::fvec2 pos, vel;

public:
	Circle();
	float getRadius();
	arma::fvec2 getPos();
	void setPos(arma::fvec2 _pos);
	sf::Vector2f getSfPos();
	arma::fvec2 getVel();
	void setVel(arma::fvec2 _vel);
	void travel(float time); // moves the object by time * velocity
};
