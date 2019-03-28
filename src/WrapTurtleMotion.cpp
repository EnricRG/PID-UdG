#include "WrapTurtleMotion.h"
#include "FenceTurtleMotion.h"
#include "CommonUtils.h"

#include <iostream>
const float MARGIN = (float) 0.001;

WrapTurtleMotion::WrapTurtleMotion()
{
}


WrapTurtleMotion::~WrapTurtleMotion()
{
}

TurtleMove::const_iterator * WrapTurtleMotion::computeDestination(Point2D actual_position, double direction, double distance, WindowSpec window) const
{
	if (BorderHitCalculator::positionInsideScreen(actual_position, window)) {
		std::vector<TurtleMove> moves;
		double remaining_distance = distance;

		Point2D previous_position = actual_position;
		std::pair<Point2D, BorderHitCalculator::border_hit> hit;

		while (remaining_distance > (0 + MARGIN)) {
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
	else return new TurtleMove::single_move_const_iterator(TurtleMove(actual_position));
}

TurtleMove WrapTurtleMotion::computeWrap(Point2D p, BorderHitCalculator::border_hit hit, WindowSpec window) const
{
	TurtleMove move;

	switch (hit) {
		case BorderHitCalculator::BOTTOM_LEFT_CORNER_HIT:
			move = TurtleMove( Point2D((float) window.width - 1 - MARGIN, (float) window.height - 1 - MARGIN) );
			break;
		case BorderHitCalculator::LEFT_EDGE_HIT:
			move = TurtleMove( Point2D((float) window.width - 1 - MARGIN, p.y) );
			break;
		case BorderHitCalculator::TOP_LEFT_CORNER_HIT:
			move = TurtleMove( Point2D((float) window.width - 1 - MARGIN, 0 + MARGIN) );
			break;
		case BorderHitCalculator::TOP_EDGE_HIT:
			move = TurtleMove( Point2D(p.x, 0 + MARGIN) );
			break;
		case BorderHitCalculator::TOP_RIGHT_CORNER_HIT:
			move = TurtleMove( Point2D(0 + MARGIN, 0 + MARGIN) );
			break;
		case BorderHitCalculator::RIGHT_EDGE_HIT:
			move = TurtleMove( Point2D(0 + MARGIN, p.y) );
			break;
		case BorderHitCalculator::BOTTOM_RIGHT_CORNER_HIT:
			move = TurtleMove( Point2D(0 + MARGIN, (float) window.height - 1 - MARGIN) );
			break;
		case BorderHitCalculator::BOTTOM_EDGE_HIT:
			move = TurtleMove( Point2D(p.x, (float) window.height - 1 - MARGIN) );
			break;
		default: //NO_HIT goes here
			move = TurtleMove(p);
			break;
	}

	return move;
}
