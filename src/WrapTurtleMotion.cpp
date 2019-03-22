#include "WrapTurtleMotion.h"
#include "FenceTurtleMotion.h"
#include "CommonUtils.h"

#include <iostream>
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
	std::pair<Point2D, BorderHitCalculator::border_hit> hit;

	while (remaining_distance > (0 + MARGIN) ) {
		hit = BorderHitCalculator::computeHit(previous_position, direction, remaining_distance, window); //compute last point before wrapping (if needed) and if it has fit any border or corner.

		remaining_distance -= hit.first.distance(previous_position); 
		previous_position = hit.first;

		std::cout << "Hit:  " << previous_position.x << " " << previous_position.y << " Hit type: " << hit.second << std::endl;
		std::cout << "Distance remaining: " << remaining_distance << std::endl;
		TurtleMove next_move = TurtleMove(hit.first, true); //visible turtle move
		moves.push_back(next_move);

		if (hit.second != BorderHitCalculator::NO_HIT) { //border teleportation
			next_move = computeWrap(next_move.getDestination(), hit.second, window);
			previous_position = next_move.getDestination();
			moves.push_back(next_move);
			remaining_distance -= 1; //border wrap consumes 1 distance unit.
			std::cout << "Warp: " << previous_position.x << " " << previous_position.y << std::endl;
		}
	}

	return new TurtleMove::multiple_move_const_iterator(moves);
}

TurtleMove WrapTurtleMotion::computeWrap(Point2D p, BorderHitCalculator::border_hit hit, WindowSpec window) const
{
	TurtleMove move;

	switch (hit) {
		case BorderHitCalculator::BOTTOM_LEFT_CORNER_HIT:
			move = TurtleMove( Point2D((float) window.width - 1, (float) window.height - 1) );
			break;
		case BorderHitCalculator::LEFT_EDGE_HIT:
			move = TurtleMove( Point2D((float) window.width - 1, p.y) );
			break;
		case BorderHitCalculator::TOP_LEFT_CORNER_HIT:
			move = TurtleMove( Point2D((float) window.width - 1, 0) );
			break;
		case BorderHitCalculator::TOP_EDGE_HIT:
			move = TurtleMove( Point2D(p.x, 0) );
			break;
		case BorderHitCalculator::TOP_RIGHT_CORNER_HIT:
			move = TurtleMove( Point2D(0, 0) );
			break;
		case BorderHitCalculator::RIGHT_EDGE_HIT:
			move = TurtleMove( Point2D(0, p.y) );
			break;
		case BorderHitCalculator::BOTTOM_RIGHT_CORNER_HIT:
			move = TurtleMove( Point2D(0, (float) window.height - 1) );
			break;
		case BorderHitCalculator::BOTTOM_EDGE_HIT:
			move = TurtleMove( Point2D(p.x, (float) window.height - 1) );
			break;
		default: //NO_HIT goes here
			move = TurtleMove(p);
			break;
	}

	return move;
}
