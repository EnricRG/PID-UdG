#include "WindowTurtleMotion.h"
#include <cmath>


WindowTurtleMotion::WindowTurtleMotion()
{
}


WindowTurtleMotion::~WindowTurtleMotion()
{
}

TurtleMove::const_iterator * WindowTurtleMotion::computeDestination(Point2D actual_position, float direction, float distance, WindowSpec window) const
{
	float x, y;
	x = actual_position.x + distance * cos(direction);
	y = actual_position.y + distance * sin(direction);
	return new TurtleMove::single_move_const_iterator(TurtleMove(Point2D(x, y), true));
}
