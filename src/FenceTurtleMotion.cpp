#include "FenceTurtleMotion.h"
#include <cmath>

#include "BorderHitCalculator.h"

FenceTurtleMotion::FenceTurtleMotion()
{
}

FenceTurtleMotion::~FenceTurtleMotion()
{
}

TurtleMove::const_iterator * FenceTurtleMotion::computeDestination(Point2D actual_position, double direction, double distance, WindowSpec window) const
{
	if (BorderHitCalculator::positionInsideScreen(actual_position, window)) {
		Point2D hit = BorderHitCalculator::computeHit(actual_position, direction, distance, window).first;

		return new TurtleMove::single_move_const_iterator(TurtleMove(hit, true));
	}
	else return new TurtleMove::single_move_const_iterator(TurtleMove(actual_position));
}
