#ifndef WINDOWTURTLEMODE_H
#define WINDOWTURTLEMODE_H

#include "TurtleMotion.h"

class WindowTurtleMotion : public TurtleMotion
{
public:
	WindowTurtleMotion();
	~WindowTurtleMotion();

	TurtleMove::const_iterator * computeDestination(Point2D actual_position, float direction, float distance, WindowSpec window) const;
	int type() const { return WINDOW_MODE; }
};

#endif