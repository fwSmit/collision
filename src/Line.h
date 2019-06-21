#include <armadillo>

class Line{
	arma::fvec2 start, end;
public:
	Line(const arma::fvec2 _start, const arma::fvec2 _end) : start(_start), end(_end){}
	// Ax + By = c
	float getA() const { return end[1] - start[1]; } 
	float getB() const { return start[0] - end[0]; }
	float getC() const { return getA()*start[0] + getB() * start[1];}
	arma::fvec2 getStart() const { return start; }
	arma::fvec2 getEnd() const { return end; }
	arma::fvec2 getDirection() const {return arma::fvec2{getB(), -getA()}; }
	arma::fvec2 getPerpendicular() const {return arma::fvec2{getA(), getB()}; }
};
