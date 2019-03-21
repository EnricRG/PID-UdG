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
		hit = computeHit(previous_position, direction, remaining_distance, window); //compute last point before wrapping (if needed) and if it has fit any border or corner.

		remaining_distance -= hit.first.distance(previous_position); 
		previous_position = hit.first;

		TurtleMove next_move = TurtleMove(hit.first, true); //visible turtle move
		moves.push_back(next_move);

		if (hit.second != NO_HIT) { //border teleportation
			next_move = computeWrap(next_move.getDestination(), hit.second, window);
			previous_position = next_move.getDestination();
			moves.push_back(next_move);
			remaining_distance -= 1; //border wrap consumes 1 distance unit.
		}
	}

	return new TurtleMove::multiple_move_const_iterator(moves);
}

std::pair<Point2D, WrapTurtleMotion::border_hit> WrapTurtleMotion::computeHit(Point2D previous_pos, float direction, float distance, WindowSpec window) const
{
	double norm_direction = normalise(direction, 0, 2*M_PI);

	Point2D hit_point;
	border_hit hit_type;
	
	//You should imagine that the screen is being "split" by its reverse diagonal (bottom left to top right corners). This way we exectue less calculations and the function runs faster.
	//This is a simplification, because the line that splits the screen is not a straight line. It's a division made to separate the top and left edges' calculations from the others.

	double angle_to_tr_corner = normalise(atan2(window.height - previous_pos.y, window.width - previous_pos.x) , 0, 2 * M_PI);	//Angle between X axis and the line that joins point previous_pos with top right corner.
	double angle_to_bl_corner = normalise(atan2(-1 - previous_pos.y, -1 - previous_pos.x), 0, 2 * M_PI);						//Angle between X axis and the line that joins point previous_pos with bottom left corner.
	
	double alpha, beta; //angles needed in order to compute the hit points.

	if (norm_direction > angle_to_tr_corner && norm_direction < angle_to_bl_corner) {		//if the direction is pointing to the top or left border.
		double angle_to_tl_corner = normalise(atan2(window.height - previous_pos.y, - 1 - previous_pos.x), 0, 2 * M_PI);		//Angle between X axis and the line that joins point previous_pos with top left corner.
		
		if (norm_direction < angle_to_tl_corner) { //direction points to top edge.
			alpha = angle_to_tl_corner - norm_direction;
			beta = norm_direction;
			double x = ( previous_pos.distance(Point2D(0, (float) window.height - 1)) * sin(alpha) ) / sin(beta);
			
			hit_point = Point2D((float) x, (float) window.height - 1);
			hit_type = TOP_EDGE_HIT;
		}
		else if (norm_direction > angle_to_tl_corner) { //direction points to left edge.
			alpha = angle_to_bl_corner - norm_direction;
			beta = norm_direction - M_PI_4;
			double y = (previous_pos.distance(Point2D(0, 0)) * sin(alpha)) / sin(beta);
			
			hit_point = Point2D(0, (float) y);
			hit_type = LEFT_EDGE_HIT;
		}
		else { //norm_direction == angle_to_tl_corner, direction is pointing to the top left corner.
			hit_point = Point2D(0, (float) window.height - 1);
			hit_type = TOP_LEFT_CORNER_HIT;
		}
	}
	else if (norm_direction < angle_to_tr_corner && norm_direction > angle_to_bl_corner){	//if the direction is not pointing to the top or left border.
		double angle_to_br_corner = normalise(atan2(-1 - previous_pos.y, window.width - previous_pos.x), 0, 2 * M_PI);			//Angle between X axis and the line that joins point previous_pos with bottom right corner.

		if (norm_direction < angle_to_br_corner) { //if direction points to bottom edge
			alpha = norm_direction - angle_to_bl_corner;
			beta = 2 * M_PI - norm_direction;
			double x = (previous_pos.distance(Point2D(0, 0)) * sin(alpha)) / sin(beta);

			hit_point = Point2D((float) x, 0);
			hit_type = BOTTOM_EDGE_HIT;
		}
		else if (norm_direction > angle_to_br_corner) { //if direction points to right edge, we have to bear in mind that in this case the transition between 2*PI and 0 occurs.
			if (direction >= 0) { //rotate all angles 90 degrees in order to avoid conditionals.
				norm_direction = normalise(norm_direction - M_PI_4, 0, 2 * M_PI);
				angle_to_br_corner = normalise(angle_to_br_corner - M_PI_4, 0, 2 * M_PI);
			}
			
			alpha = norm_direction - angle_to_br_corner;
			beta = 2 * M_PI - norm_direction;
			double y = (previous_pos.distance(Point2D((float) window.width - 1, (float) 0)) * sin(alpha)) / sin(beta);

			hit_point = Point2D((float) window.width - 1, (float) y);
			hit_type = RIGHT_EDGE_HIT;
		}
		else { //norm_direction == angle_to_br_corner, direction is pointing to the bottom right corner.
			hit_point = Point2D((float) window.width - 1, 0);
			hit_type = BOTTOM_RIGHT_CORNER_HIT;
		}
	}
	else if(norm_direction == angle_to_tr_corner) {											//if the direction is pointing to the top right corenr.
		hit_point = Point2D((float) window.width - 1, (float) window.height - 1);
		hit_type = TOP_RIGHT_CORNER_HIT;
	}
	else {																					//norm_direction == angle_to_bl_corner, the direction is pointing to the bottom left corner.
		hit_point = Point2D(0, 0);
		hit_type = BOTTOM_LEFT_CORNER_HIT;
	}																				

	double movement_dist = previous_pos.distance(hit_point);

	if (movement_dist > distance) { //if we don't have enough remaining distance to hit the border
		double scale_ratio = distance / movement_dist;
		hit_point = Point2D(previous_pos.x + (hit_point.x - previous_pos.x) * (float) scale_ratio, previous_pos.y + (hit_point.y - previous_pos.y) * (float) scale_ratio);
		hit_type = NO_HIT;
	}

	return std::pair<Point2D, border_hit>(hit_point, hit_type);
}

TurtleMove WrapTurtleMotion::computeWrap(Point2D p, border_hit hit, WindowSpec window) const
{
	TurtleMove move;

	switch (hit) {
		case BOTTOM_LEFT_CORNER_HIT:
			move = TurtleMove( Point2D((float) window.width - 1, (float) window.height - 1) );
			break;
		case LEFT_EDGE_HIT:
			move = TurtleMove( Point2D((float) window.width - 1, p.y) );
			break;
		case TOP_LEFT_CORNER_HIT:
			move = TurtleMove( Point2D((float) window.width - 1, 0) );
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
			move = TurtleMove( Point2D(0, (float) window.height - 1) );
			break;
		case BOTTOM_EDGE_HIT:
			move = TurtleMove( Point2D(p.x, (float) window.height - 1) );
			break;
		default: //NO_HIT goes here
			move = TurtleMove(p);
			break;
	}

	return move;
}
