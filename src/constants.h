#pragma once
#include <armadillo>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "Physics.h"

class Circle_internal;
class Physics;

namespace constants{
	const float scale = 1.f; // pixels / meter
	const sf::Vector2i windowSize(800, 800);
}
namespace op{ // open for all classes
	template<typename T>
		class Singleton
		{
			public:
				static T* GetInstance();
				static void destroy();

			private:

				Singleton(Singleton const&)
				{
				};
				Singleton& operator=(Singleton const&)
				{
				};

			protected:
				static T* m_instance;

				Singleton()
				{
					m_instance = static_cast <T*> (this);
				};
				~Singleton()
				{
				};
		};

	sf::Vector2f toSf(arma::fvec2 vec);
	float toSf(float val);
	arma::fvec2 toArma(sf::Vector2f vec);
	arma::fvec2 toArma(sf::Vector2u vec);
	arma::fvec2 toArma(sf::Vector2i vec);
	float toArma(float val);
	void drawPoint(arma::fvec2 p);
	void drawPoint(arma::fvec2 p, sf::Color color);
	void drawArrow(sf::Vector2f a, sf::Vector2f b);
	arma::fvec2 getParalel(arma::fvec2 start, arma::fvec2 paralelTo);
	sf::Vector2f getMousePos();
	bool isMouseInWindow();
	bool isMouseOnAnyWidget(tgui::Gui& gui);
	bool isCircleInBounds(Circle_internal c);
	// void createWindow(sf::VideoMode mode, const sf::String &title, sf::Uint32 style=sf::Style::Default, const sf::ContextSettings &settings=sf::ContextSettings());
	sf::RenderWindow& getWindow();
	// void createPhysics();
	Physics& getPhysics();
	//float distance(arma::fvec2 a, arma::fvec2 b);
	//arma::fvec2 getIntersection(Line a, Line b);
}
