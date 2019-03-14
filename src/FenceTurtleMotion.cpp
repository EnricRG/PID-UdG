#include "FenceTurtleMotion.h"
#include <cmath>


FenceTurtleMotion::FenceTurtleMotion()
{
}


FenceTurtleMotion::~FenceTurtleMotion()
{
}

Point2D FenceTurtleMotion::nextPosition(Point2D actual_position, float direction, float distance, WindowSpec window)
{	
	float x, y;

	x = actual_position.x + distance * cos(direction);
	y = actual_position.y + distance * sin(direction);

	x = (x < 0) ? 0 : 
		(x > window.width) ? window.width : x;
	
	y = (y < 0) ? 0 :
		(y > window.height) ? window.height : y;
	
	return Point2D(x,y);
}

TurtleMove::const_iterator * FenceTurtleMotion::computeDestination(Point2D actual_position, float direction, float distance, WindowSpec window)
{
	float x, y;

	x = actual_position.x + distance * cos(direction);
	y = actual_position.y + distance * sin(direction);

	x = (x < 0) ? 0 :
		(x > window.width) ? window.width : x;

	y = (y < 0) ? 0 :
		(y > window.height) ? window.height : y;

	return new TurtleMove::single_move_const_iterator(TurtleMove(Point2D(x, y), true));
}
