#include "constants.h"
#include "Circle_internal.h"
#include "Physics.h"

namespace op{
	using namespace constants;

	window_struct::~window_struct(){
		delete window;
		delete physics;
	}
	
	sf::Vector2f toSf(arma::fvec2 vec) { 
		sf::Vector2f result;
		result.x = toSf(vec[0]);
		result.y = toSf(vec[1]);
		return result;
	}

	float toSf(float val){
		return val * scale;
	}

	arma::fvec2 toArma(sf::Vector2f vec){
		return arma::fvec2{toArma(vec.x), toArma(vec.y)};
	}

	arma::fvec2 toArma(sf::Vector2u vec){
		return arma::fvec2{toArma(vec.x), toArma(vec.y)};
	}

	arma::fvec2 toArma(sf::Vector2i vec){
		return arma::fvec2{toArma(vec.x), toArma(vec.y)};
	}

	float toArma(float val){
		return val/scale;
	}
	void drawPoint(arma::fvec2 p){
		sf::CircleShape circle;
		circle.setPosition(op::toSf(p));
		circle.setRadius(3);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setFillColor(sf::Color::Red);
		getWindow().draw(circle);
	}
	
	void drawPoint(arma::fvec2 p, sf::Color color){
		sf::CircleShape circle;
		circle.setPosition(op::toSf(p));
		circle.setRadius(3);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setFillColor(color);
		getWindow().draw(circle);
	}

	arma::fvec2 getParalel(arma::fvec2 start, arma::fvec2 paralelTo){
		arma::fvec2 paralel = paralelTo * (arma::dot(paralelTo, start) / (pow(arma::norm(paralelTo), 2)));
		
		//arma::fvec2 perpendicular_i = start - paralel_i;
		return paralel;
	}
	
	sf::Vector2f getMousePos(){
		return sf::Vector2f(sf::Mouse::getPosition(getWindow()));
	}
	
	//float distance(arma::fvec2 a, arma::fvec2 b){
		//arma::fvec2 deltaPos = a - b;
	//}
	
	void drawArrow(sf::Vector2f a, sf::Vector2f b){

		sf::VertexArray line;
		line.setPrimitiveType(sf::PrimitiveType::Lines);
		line.append(a);
		line.append(b);
		getWindow().draw(line);
	}
	
	bool isMouseInWindow(){
		auto mousePos = sf::Mouse::getPosition(getWindow());
		auto windowSize = getWindow().getSize();
		bool inWindow = true;
		if(mousePos.x < 0 || mousePos.y < 0 || mousePos.x > windowSize.x || mousePos.y > windowSize.y){
			inWindow = false;
		}
		return inWindow;
	}
	bool isMouseOnAnyWidget(tgui::Gui& gui)
	{
		auto allWidgets = gui.getWidgets();
		bool mouseOnWidget = false;
		for(auto widget : allWidgets){
			if(widget->mouseOnWidget(op::getMousePos())){
				mouseOnWidget = true;
				break;
			}
			if(widget->getWidgetType() == "Slider"){
				auto slider = widget->cast<tgui::Slider>();
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && slider->isFocused()){
					mouseOnWidget = true;
					break;
				}
			}
		}
		return mouseOnWidget;
	}
	
	bool isCircleInBounds(Circle_internal c){
		return true;
	}
	
	void createWindow(sf::VideoMode mode, const sf::String &title, sf::Uint32 style, const sf::ContextSettings &settings){
		if(internal.window != nullptr)
		{
			internal.window = new sf::RenderWindow(mode, title, style, settings);
		}
	}

	sf::RenderWindow& getWindow(){
		return *internal.window;
	}

	void createPhysics(){
		if(internal.physics != nullptr)
		{
			internal.physics = new Physics();	
		}
	}

	Physics& getPhysics(){
		return *internal.physics;	
	}
}

