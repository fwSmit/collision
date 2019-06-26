#include "Circle.h"
#include "constants.h"
#include "Physics.h"

Circle::Circle(){
	it = op::getPhysics().addObject({20, 30}, {500, 200}, 60);
}

Circle::~Circle(){
	op::getPhysics().removeCircle(it);
}
