#pragma once
#include "Circle_internal.h"
#include "Line.h"
#include <SFML/Graphics.hpp>
#include <armadillo>
#include <list>

using Store_t = std::list<Circle_internal>;
using Iter_t = Store_t::iterator;

class Physics{
	Store_t objects;
	std::vector<sf::CircleShape> circles;
	sf::VertexArray lines_array;
	std::list<Line> lines;
	arma::fvec2 bounds;
	arma::fvec2 closestPointOnLine(Line line, arma::fvec2 p); // returns the point on the line that is closest to p
	bool hasWalls = false;
	const unsigned int n_walls = 4;
	
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
	Iter_t addObject(arma::fvec2 pos, arma::fvec2 vel);
	Iter_t addObject(arma::fvec2 pos, arma::fvec2 vel, float radius);
	Iter_t addObject(Circle_internal object, sf::Color fillColor = sf::Color::Blue);
	std::list<Line>::iterator addLine(arma::fvec2 start, arma::fvec2 end);
	void draw();
	void update(float deltaTime);
	std::size_t getNumObjects();
	std::size_t getNumLines();
	void reset();
	void setObjectColor(std::size_t id, sf::Color color);
	void createWalls();
	void setWalls(bool hasWalls); // should there be wall at the side of the screen?
};
