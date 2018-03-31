#pragma once
#include <armadillo>
#include <SFML/System/Vector2.hpp>

namespace constants{
	const float scale = 2.f; // pixels / meter
}
namespace op{ // open for all classes
	sf::Vector2f toSf(arma::fvec2 vec);
	float toSf(float val);
	arma::fvec2 toArma(sf::Vector2f vec);
	arma::fvec2 toArma(sf::Vector2u vec);
	float toArma(float val);
}
