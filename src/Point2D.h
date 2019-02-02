#ifndef POINT2D_H
#define POINT2D_H

/// @brief Pair of coordinates.
/** Struct that contains the information of a 2D point: its X and Y coordinates.
*/
struct Point2D {
	float x, /**< X coordinate.*/
		  y; /**< Y coordinate.*/

	/** Default constructor
	*/
	Point2D() { x = 0; y = 0; }
	
	/** Parametric constructor of the class.
	*	@param x X coordinate of the point.
	*	@param y Y coordinate of the point.
	*/
	Point2D(float x, float y) { this->x = x; this->y = y; }

	/** Operator that defines the addition operation between two points.
	*	@param p The other point.
	*/
	Point2D operator+(const Point2D & p) { return Point2D(x + p.x, y + p.y); }
	
	/** Operator that defines the subtraction operation between two points.
	*	@param p The other point.
	*/
	Point2D operator-(const Point2D & p) { return Point2D(x - p.x, y - p.y); }
};

#endif