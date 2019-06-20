#include <armadillo>

class Line{
	arma::fvec2 start, end;
public:
	Line(const arma::fvec2 _start, const arma::fvec2 _end) : start(_start), end(_end){}
	// Ax + By = c
	const float getA(){ return end[1] - start[1]; } 
	const float getB(){ return start[0] - end[0]; }
	const float getC(){ return getA()*start[0] + getB() * start[1];}
	const arma::fvec2 getStart() { return start; }
	const arma::fvec2 getEnd() { return end; }
	const arma::fvec2 getDirection() {return arma::fvec2{getB(), -getA()}; }
	const arma::fvec2 getPerpendicular() {return arma::fvec2{getA(), getB()}; }
};
