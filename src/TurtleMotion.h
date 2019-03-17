#ifndef TURTLEMOTION_H
#define TURTLEMOTION_H

#include "WindowSpec.h"
#include "TurtleMove.h"
#include "Point2D.h"

static const int WRAP_MODE = 1;		//When turtle runs to an edge of the screen, it appears on the opposite edge
static const int WINDOW_MODE = 2;	//When turtle runs to an edge of the screen, it continues forward outside the screen
static const int FENCE_MODE = 3;	//When turtle runs to an edge of the screen, it stops

class TurtleMotion 
{
public:
	virtual ~TurtleMotion() {};
	virtual TurtleMove::const_iterator * computeDestination(Point2D actual_position, float direction, float distance, WindowSpec window) const = 0;
	virtual int type() const = 0;
};

#endif