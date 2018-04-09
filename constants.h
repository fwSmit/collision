#pragma once
#include <armadillo>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

namespace constants{
	const float scale = 2.f; // pixels / meter
}
namespace op{ // open for all classes
	sf::Vector2f toSf(arma::fvec2 vec);
	float toSf(float val);
	arma::fvec2 toArma(sf::Vector2f vec);
	arma::fvec2 toArma(sf::Vector2u vec);
	arma::fvec2 toArma(sf::Vector2i vec);
	float toArma(float val);
	void drawPoint(arma::fvec2 p, sf::RenderWindow& window);
}
