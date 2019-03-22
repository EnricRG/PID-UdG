#ifndef WRAPTURTLEMODE_H
#define WRAPTURTLEMODE_H

#include "TurtleMotion.h"
#include "BorderHitCalculator.h"

class WrapTurtleMotion : public TurtleMotion
{
public:
	WrapTurtleMotion();
	~WrapTurtleMotion();

	TurtleMove::const_iterator * computeDestination(Point2D actual_position, double direction, double distance, WindowSpec window) const;
	int type() const { return WRAP_MODE; }

private:
	TurtleMove computeWrap(Point2D p, BorderHitCalculator::border_hit hit, WindowSpec window) const;
};

#endif
