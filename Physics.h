#include <armadillo>
#include <vector>
#include "Circle.h"
#include "Line.h"
#include <SFML/Graphics.hpp>

class Physics{
	std::vector<Circle> objects;
	std::vector<sf::CircleShape> circles;
	sf::VertexArray lines_array;
	std::vector<Line> lines;
	sf::RenderWindow& window;
	arma::fvec2 bounds;
	arma::fvec2 closestPointOnLine(Line line, arma::fvec2 p); // returns the point on the line that is closest to p
	void travelAll(float time);
	void mouseDrag(float deltaTime); // lets the user move circle with the mouse
public:
	Physics(sf::RenderWindow& window);
	void addObject(arma::fvec2 pos, arma::fvec2 vel);
	void addObject(arma::fvec2 pos, arma::fvec2 vel, float radius);
	void addObject(Circle object);
	void addLine(arma::fvec2 start, arma::fvec2 end);
	void draw(float deltaTime);
	void update(float deltaTime);
};
