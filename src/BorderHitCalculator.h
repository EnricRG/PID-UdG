#ifndef BORDERHITCALCULATOR_H
#define BORDERHITCALCULATOR_H

#include "Point2D.h"
#include "WindowSpec.h"
#include <utility>

class BorderHitCalculator
{
public:
	enum border_hit {
		BOTTOM_LEFT_CORNER_HIT, LEFT_EDGE_HIT, TOP_LEFT_CORNER_HIT, TOP_EDGE_HIT,
		TOP_RIGHT_CORNER_HIT, RIGHT_EDGE_HIT, BOTTOM_RIGHT_CORNER_HIT, BOTTOM_EDGE_HIT,
		NO_HIT
	};

	static std::pair<Point2D, BorderHitCalculator::border_hit> computeHit(Point2D previous_pos, double direction, double distance, WindowSpec window);

private:
	BorderHitCalculator() {};
	~BorderHitCalculator() {};
};

#endif