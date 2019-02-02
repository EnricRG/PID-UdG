#ifndef TURTLEMOTIONFACTORY_H
#define TURTLEMOTIONFACTORY_H

#include "TurtleMotion.h"

class TurtleMotionFactory
{
public:
	TurtleMotionFactory();
	~TurtleMotionFactory();

	static TurtleMotion* makeTurtleMotion(int motion_type);
};

#endif