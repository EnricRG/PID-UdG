#include "WrapTurtleMotion.h"
#include "FenceTurtleMotion.h"
#include "CommonUtils.h"

#define _USE_MATH_DEFINES
#include <math.h>

const float MARGIN = (float) 0.01;

WrapTurtleMotion::WrapTurtleMotion()
{
}


WrapTurtleMotion::~WrapTurtleMotion()
{
}

TurtleMove::const_iterator * WrapTurtleMotion::computeDestination(Point2D actual_position, float direction, float distance, WindowSpec window) const
{
	std::vector<TurtleMove> moves;
	float remaining_distance = distance;

	Point2D previous_position = actual_position;
	std::pair<Point2D, border_hit> hit;

	while (remaining_distance > (0 + MARGIN) ) {
		//detect precise first border hit
		//compute precise hit point
		hit = computeHit(previous_position, direction, distance, window);

		remaining_distance -= hit.first.distance(previous_position);
		previous_position = hit.first;

		TurtleMove next_move = TurtleMove(hit.first, true); //visible turtle move
		moves.push_back(next_move);

		if (hit.second != NO_HIT) { //border teleportation
			next_move = computeWrap(next_move.getDestination(), hit.second, window);
			previous_position = next_move.getDestination();
			moves.push_back(next_move);
		}
	}

	return new TurtleMove::multiple_move_const_iterator(moves);
}

std::pair<Point2D, WrapTurtleMotion::border_hit> WrapTurtleMotion::computeHit(Point2D previous_pos, float direction, float distance, WindowSpec window) const
{
	float norm_direction = normalise(direction, 0, 2 * M_PI);
	Point2D hit_point;

	unsigned quadrant = (norm_direction >= 0 && norm_direction < M_PI) ?
		(norm_direction < M_PI_2)? 1 : 2
		:
		(norm_direction < M_PI+M_PI_2) ? 3 : 4;

	float y = tan(norm_direction)*(window.width - previous_pos.x);

	//TODO: calcular punt de tall amb els marges i marge concret (border_hit)

	//hit

	return std::pair<Point2D, border_hit>();
}

TurtleMove WrapTurtleMotion::computeWrap(Point2D p, border_hit hit, WindowSpec window) const
{
	TurtleMove move;

	switch (hit) {
		case BOTTOM_LEFT_CORNER_HIT:
			move = TurtleMove( Point2D(window.width - 1, window.height - 1) );
			break;
		case LEFT_EDGE_HIT:
			move = TurtleMove( Point2D(window.width - 1, p.y) );
			break;
		case TOP_LEFT_CORNER_HIT:
			move = TurtleMove( Point2D(window.width - 1, 0) );
			break;
		case TOP_EDGE_HIT:
			move = TurtleMove( Point2D(p.x, 0) );
			break;
		case TOP_RIGHT_CORNER_HIT:
			move = TurtleMove( Point2D(0, 0) );
			break;
		case RIGHT_EDGE_HIT:
			move = TurtleMove( Point2D(0, p.y) );
			break;
		case BOTTOM_RIGHT_CORNER_HIT:
			move = TurtleMove( Point2D(0, window.height - 1) );
			break;
		case BOTTOM_EDGE_HIT:
			move = TurtleMove( Point2D(p.x, window.height - 1) );
			break;
		default: //NO_HIT goes here
			move = TurtleMove(p);
			break;
	}

	return move;
}
