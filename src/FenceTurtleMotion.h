#ifndef FENCETURTLEMODE_H
#define FENCETURTLEMODE_H

#include "TurtleMotion.h"

/// @brief
class FenceTurtleMotion : public TurtleMotion
{
public:
	FenceTurtleMotion();
	~FenceTurtleMotion();

	TurtleMove::const_iterator * computeDestination(Point2D actual_position, double direction, double distance, WindowSpec window) const;
	int type() const { return FENCE_MODE; }
};

#endif