#include <armadillo>

class Line{
	arma::fvec2 start, end;
public:
	Line(arma::fvec2 _start, arma::fvec2 _end) : start(_start), end(_end){}
	// Ax + By = c
	float getA(){ return end[1] - start[1]; } 
	float getB(){ return start[0] - end[0]; }
	float getC(){ return getA()*start[0] + getB() * start[1];}
	arma::fvec2 getStart() { return start; }
	arma::fvec2 getEnd() { return end; }
};
