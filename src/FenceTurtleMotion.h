#ifndef FENCETURTLEMODE_H
#define FENCETURTLEMODE_H

#include "TurtleMotion.h"

/// @brief
class FenceTurtleMotion : public TurtleMotion
{
public:
	FenceTurtleMotion();
	~FenceTurtleMotion();

	Point2D nextPosition(Point2D actual_position, float direction, float distance, WindowSpec window);
	TurtleMove::const_iterator * computeDestination(Point2D actual_position, float direction, float distance, WindowSpec window);
	int type() { return FENCE_MODE; }
};

#endif