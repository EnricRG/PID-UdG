#ifndef WRAPTURTLEMODE_H
#define WRAPTURTLEMODE_H

#include "TurtleMotion.h"

class WrapTurtleMotion : public TurtleMotion
{
public:
	WrapTurtleMotion();
	~WrapTurtleMotion();

	TurtleMove::const_iterator * computeDestination(Point2D actual_position, float direction, float distance, WindowSpec window) const;
	int type() const { return WRAP_MODE; }

protected:
	enum border_hit {
		BOTTOM_LEFT_CORNER_HIT, LEFT_EDGE_HIT, TOP_LEFT_CORNER_HIT, TOP_EDGE_HIT, 
		TOP_RIGHT_CORNER_HIT, RIGHT_EDGE_HIT, BOTTOM_RIGHT_CORNER_HIT, BOTTOM_EDGE_HIT, 
		NO_HIT
	};

private:
	std::pair<Point2D, WrapTurtleMotion::border_hit> computeHit(Point2D previous_pos, float direction, float distance, WindowSpec window) const;
	TurtleMove computeWrap(Point2D p, border_hit hit, WindowSpec window) const;
};

#endif
