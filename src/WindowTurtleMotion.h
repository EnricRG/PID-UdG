#ifndef WINDOWTURTLEMODE_H
#define WINDOWTURTLEMODE_H

#include "TurtleMotion.h"

class WindowTurtleMotion : public TurtleMotion
{
public:
	WindowTurtleMotion();
	~WindowTurtleMotion();

	Point2D nextPosition(Point2D actual_position, float direction, float distance, WindowSpec window);
	int type() { return WINDOW_MODE; }
};

#endif