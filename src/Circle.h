#pragma once
#include "Circle_internal.h"
#include <list>

class Circle{
	std::list<Circle_internal>::iterator it;
public:
	Circle();
	~Circle();
};
