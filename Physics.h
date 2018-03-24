#include <armadillo>
#include <vector>
#include "Circle.h"
#include <SFML/Graphics.hpp>

class Physics{
	bool end = false;
	void update(float deltaTime);
	std::vector<Circle> objects;
	std::vector<sf::CircleShape> circles;
	sf::RenderWindow& window;
	arma::fvec2 bounds;
public:
	Physics(sf::RenderWindow& window);
	void addObject(arma::fvec2 pos, arma::fvec2 vel);
	void draw(float deltaTime);
};
