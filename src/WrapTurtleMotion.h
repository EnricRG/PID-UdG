#ifndef WRAPTURTLEMODE_H
#define WRAPTURTLEMODE_H

#include "TurtleMotion.h"

class WrapTurtleMotion : public TurtleMotion
{
public:
	WrapTurtleMotion();
	~WrapTurtleMotion();

	Point2D nextPosition(Point2D actual_position, float direction, float distance, WindowSpec window);
	TurtleMove::const_iterator * computeDestination(Point2D actual_position, float direction, float distance, WindowSpec window);
	int type() { return WRAP_MODE; }
};

#endif
