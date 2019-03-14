#include "WindowTurtleMotion.h"
#include <cmath>


WindowTurtleMotion::WindowTurtleMotion()
{
}


WindowTurtleMotion::~WindowTurtleMotion()
{
}

Point2D WindowTurtleMotion::nextPosition(Point2D actual_position, float direction, float distance, WindowSpec window)
{
	float x, y;
	x = actual_position.x + distance * cos(direction);
	y = actual_position.y + distance * sin(direction);
	return Point2D(x,y);
}

TurtleMove::const_iterator * WindowTurtleMotion::computeDestination(Point2D actual_position, float direction, float distance, WindowSpec window)
{
	float x, y;
	x = actual_position.x + distance * cos(direction);
	y = actual_position.y + distance * sin(direction);
	return new TurtleMove::single_move_const_iterator(TurtleMove(Point2D(x, y), true));
}
