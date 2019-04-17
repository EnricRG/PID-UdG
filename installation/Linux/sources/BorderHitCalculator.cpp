#include "BorderHitCalculator.h"
#include "CommonUtils.h"
#include <iostream>

#define WINDOWADDON_PI			3.14159265358979323846
#define WINDOWADDON_PI_2		1.57079632679489661923

const double MARGIN_OF_ERROR = 0.0001; //less than 0.01 degrees

bool BorderHitCalculator::positionInsideScreen(Point2D p, WindowSpec window){
	return p.x >= 0 && p.x < window.width && p.y >= 0 && p.y < window.height;
}

std::pair<Point2D, BorderHitCalculator::border_hit> BorderHitCalculator::computeHit(Point2D previous_pos, double direction, double distance, WindowSpec window)
{
	double norm_direction = normalise(direction, 0, 2 * WINDOWADDON_PI);

	Point2D hit_point;
	border_hit hit_type;

	//You should imagine that the screen is being "split" by its reverse diagonal (bottom left to top right corners). This way we exectue less calculations and the function runs faster.
	//This is a simplification, because the line that splits the screen is not a straight line. It's a division made to separate the top and left edges' calculations from the others.

	double angle_to_tr_corner = normalise(atan2(window.height - 1 - previous_pos.y, window.width - 1 - previous_pos.x), 0, 2 * WINDOWADDON_PI);	//Angle between X axis and the line that joins point previous_pos with top right corner.
	double angle_to_bl_corner = normalise(atan2( - previous_pos.y, - previous_pos.x), 0, 2 * WINDOWADDON_PI);						//Angle between X axis and the line that joins point previous_pos with bottom left corner.

	double alpha, beta; //angles needed in order to compute the hit points.

	if (norm_direction > angle_to_tr_corner && norm_direction < angle_to_bl_corner) { //if the direction is pointing to the top or left border.
		double angle_to_tl_corner = normalise(atan2(window.height - 1 - previous_pos.y, - previous_pos.x), 0, 2 * WINDOWADDON_PI); //Angle between X axis and the line that joins point previous_pos with top left corner.

		if (norm_direction < angle_to_tl_corner) { //direction points to top edge.
			alpha = angle_to_tl_corner - norm_direction;
			beta = norm_direction;
			double x = (previous_pos.distance(Point2D(0, (float)window.height - 1)) * sin(alpha)) / sin(beta);

			hit_point = Point2D((float)x, (float)window.height - 1);
			hit_type = TOP_EDGE_HIT;
		}
		else if (norm_direction > angle_to_tl_corner) { //direction points to left edge.
			alpha = angle_to_bl_corner - norm_direction;
			beta = norm_direction - WINDOWADDON_PI_2;
			double y = (previous_pos.distance(Point2D(0, 0)) * sin(alpha)) / sin(beta);

			hit_point = Point2D(0, (float)y);
			hit_type = LEFT_EDGE_HIT;
		}
		else { //norm_direction == angle_to_tl_corner, direction is pointing to the top left corner.
			
			hit_point = Point2D(0, (float)window.height - 1);
			
			if (norm_direction > WINDOWADDON_PI - MARGIN_OF_ERROR) hit_type = LEFT_EDGE_HIT; //if the direction mostly points to the left.
			else if (norm_direction > WINDOWADDON_PI_2 - MARGIN_OF_ERROR) hit_type = TOP_EDGE_HIT; //if the direction mostly points to the top.
			else hit_type = TOP_LEFT_CORNER_HIT;
		}
	}
	else if (norm_direction < angle_to_tr_corner || norm_direction > angle_to_bl_corner) { //if the direction is not pointing to the top or left border and none of the corners in that range.
		if (norm_direction < angle_to_tr_corner) norm_direction += 2 * WINDOWADDON_PI; //adding a complete turn
		
		double angle_to_br_corner = normalise(atan2( - previous_pos.y, window.width - 1 - previous_pos.x), 0, 2 * WINDOWADDON_PI); //Angle between X axis and the line that joins point previous_pos with bottom right corner.

		if (norm_direction < angle_to_br_corner) { //if direction points to bottom edge.
			alpha = norm_direction - angle_to_bl_corner;
			beta = 2 * WINDOWADDON_PI - norm_direction;
			double x = (previous_pos.distance(Point2D(0, 0)) * sin(alpha)) / sin(beta);

			hit_point = Point2D((float)x, 0);
			hit_type = BOTTOM_EDGE_HIT;
		}
		else if (norm_direction > angle_to_br_corner) { //if direction points to right edge, we have to bear in mind that in this case the transition between 2*PI and 0 occurs.
							
			norm_direction = normalise(norm_direction - WINDOWADDON_PI_2, 0, 2 * WINDOWADDON_PI); //rotate all angles 90 degrees in order to avoid conditionals.
			angle_to_br_corner = normalise(angle_to_br_corner - WINDOWADDON_PI_2, 0, 2 * WINDOWADDON_PI); //rotate all angles 90 degrees in order to avoid conditionals.

			alpha = norm_direction - angle_to_br_corner;
			beta = 2 * WINDOWADDON_PI - norm_direction;
			double y = (previous_pos.distance(Point2D((float)window.width - 1, 0)) * sin(alpha)) / sin(beta);

			hit_point = Point2D((float)window.width - 1, (float)y);
			hit_type = RIGHT_EDGE_HIT;
		}
		else { //norm_direction == angle_to_br_corner, direction is pointing to the bottom right corner.
			hit_point = Point2D((float)window.width - 1, 0);
			
			if (norm_direction > 2 * WINDOWADDON_PI - MARGIN_OF_ERROR) hit_type = RIGHT_EDGE_HIT; //if the direction mostly points to the right.
			else if (norm_direction > WINDOWADDON_PI + WINDOWADDON_PI_2 - MARGIN_OF_ERROR) hit_type = BOTTOM_EDGE_HIT; //if the direction mostly points to the bottom.
			else hit_type = BOTTOM_RIGHT_CORNER_HIT;
		}
	}
	else if (norm_direction == angle_to_tr_corner) { //if the direction is pointing to the top right corner.
		hit_point = Point2D((float)window.width - 1, (float)window.height - 1);
		
		if(norm_direction > MARGIN_OF_ERROR) hit_type = RIGHT_EDGE_HIT; //if direction mostly points to the right.
		else if(norm_direction > WINDOWADDON_PI_2 - MARGIN_OF_ERROR) hit_type = TOP_EDGE_HIT; //if direction mostly points to the top.
		else hit_type = TOP_RIGHT_CORNER_HIT;
	}
	else { //norm_direction == angle_to_bl_corner, the direction is pointing to the bottom left corner.
		hit_point = Point2D(0, 0);

		if (norm_direction > WINDOWADDON_PI - MARGIN_OF_ERROR) hit_type = LEFT_EDGE_HIT; //if direction mostly points to the right.
		else if (norm_direction > WINDOWADDON_PI + WINDOWADDON_PI_2 - MARGIN_OF_ERROR) hit_type = BOTTOM_EDGE_HIT; //if direction mostly points to the top.
		else hit_type = BOTTOM_LEFT_CORNER_HIT;
	}

	double movement_dist = previous_pos.distance(hit_point);

	if (movement_dist > distance) { //if we don't have enough remaining distance to hit the border
		double scale_ratio = distance / movement_dist;
		hit_point = Point2D(previous_pos.x + (hit_point.x - previous_pos.x) * (float)scale_ratio, previous_pos.y + (hit_point.y - previous_pos.y) * (float)scale_ratio);
		hit_type = NO_HIT;
	}

	return std::pair<Point2D, border_hit>(hit_point, hit_type);
}

