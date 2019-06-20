#pragma once
#include <armadillo>
#include <vector>
#include "Circle_internal.h"
#include "Line.h"
#include <SFML/Graphics.hpp>

class Physics{
	std::vector<Circle_internal> objects;
	std::vector<sf::CircleShape> circles;
	sf::VertexArray lines_array;
	std::vector<Line> lines;
	arma::fvec2 bounds;
	arma::fvec2 closestPointOnLine(Line line, arma::fvec2 p); // returns the point on the line that is closest to p
	void travelAll(float time);
	void mouseDrag(float deltaTime); // lets the user move circle with the mouse
	sf::RenderWindow& getWindow();
public:
	Circle_internal& getObject(int index);
	Line& getLine(int index);
	void clear();
	void removeCircle(int index);
	void removeLine(int index);
	Physics();
	void addObject(arma::fvec2 pos, arma::fvec2 vel);
	void addObject(arma::fvec2 pos, arma::fvec2 vel, float radius);
	void addObject(Circle_internal object, sf::Color fillColor = sf::Color::Blue);
	void addLine(arma::fvec2 start, arma::fvec2 end);
	void draw(float deltaTime);
	void update(float deltaTime);
	std::size_t getNumObjects();
	std::size_t getNumLines();
	void reset();
	void setObjectColor(std::size_t id, sf::Color color);
};
