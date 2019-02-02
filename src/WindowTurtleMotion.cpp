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
