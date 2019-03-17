#include "FenceTurtleMotion.h"
#include <cmath>


FenceTurtleMotion::FenceTurtleMotion()
{
}

FenceTurtleMotion::~FenceTurtleMotion()
{
}

TurtleMove::const_iterator * FenceTurtleMotion::computeDestination(Point2D actual_position, float direction, float distance, WindowSpec window) const
{
	float x, y;

	x = actual_position.x + distance * cos(direction);
	y = actual_position.y + distance * sin(direction);

	x = (x < 0) ? 0 :
		(x >= window.width) ? window.width - 1 : x;

	y = (y < 0) ? 0 :
		(y >= window.height) ? window.height - 1 : y;

	return new TurtleMove::single_move_const_iterator(TurtleMove(Point2D(x, y), true));
}
