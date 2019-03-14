#include "WrapTurtleMotion.h"

const float MARGIN = 0.01;


WrapTurtleMotion::WrapTurtleMotion()
{
}


WrapTurtleMotion::~WrapTurtleMotion()
{
}

Point2D WrapTurtleMotion::nextPosition(Point2D actual_position, float direction, float distance, WindowSpec window)
{
	return Point2D();
}

TurtleMove::const_iterator * WrapTurtleMotion::computeDestination(Point2D actual_position, float direction, float distance, WindowSpec window)
{
	std::vector<TurtleMove> moves;
	float remaining_distance = distance;

	float x, y;
	bool left_edge_hit, right_edge_hit, top_edge_hit, bottom_edge_hit;

	while (remaining_distance > (0 + MARGIN) ) {
		x = actual_position.x + distance * cos(direction);
		y = actual_position.y + distance * sin(direction);

		left_edge_hit = x < 0;
		bottom_edge_hit = y < 0;
		right_edge_hit = x > window.width;
		top_edge_hit = y > window.height;

		//TODO: comrpovar punt de teleport i afegir move al vector
	}

	return new TurtleMove::multiple_move_const_iterator(moves);
}
