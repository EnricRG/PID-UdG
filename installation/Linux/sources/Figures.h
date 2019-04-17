#ifndef FIGURES_H
#define FIGURES_H

#ifndef NULL
#define NULL 0
#endif

#include "Point2D.h"
#include "Angle.h"

#include "CommonUtils.h"

///@brief Contains some structs that can store information about some geometric figures.
/** This namespace contains a series of structs that store the information about some geometric figures usually used to draw objects on a Window. You can use them for any other purposes as well.*/
namespace figures {

	struct Line {
		Point2D p1, /**< An end point of the line. */
				p2; /**< An end point of the line. */
		
		/** Default constructor. */
		Line() {}	
		
		/** Parametric constructor. 
		*	@param p1 First end point of the line.
		*	@param p2 Last end point of the line.
		*/
		Line(Point2D p1, Point2D p2) { init(p1, p2); }
		
		/** Parametric constructor.
		*	@param x1 X coordinate of the first end point of the line.
		*	@param y1 Y coordinate of the first end point of the line.
		*	@param x2 X coordinate of the other end point of the line.
		*	@param y2 Y coordinate of the other end point of the line.
		*/
		Line(float x1, float y1, float x2, float y2) { init(Point2D(x1, y1), Point2D(x2, y2)); }

		/** Initializes the line.
		*	@param p1 First end point of the line.
		*	@param p2 Last end point of the line.
		*/
		void init(Point2D p1, Point2D p2) { this->p1 = p1; this->p2 = p2; }
	};

	struct Triangle {
		Point2D p1, /**< A vertex of the triangle.*/
				p2, /**< A vertex of the triangle.*/
				p3;	/**< A vertex of the triangle.*/

		/** Default constructor. */
		Triangle() {}
		
		/** Parametric constructor.
		*	@param p1 First vertex of the triangle.
		*	@param p2 Second vertex of the triangle.
		*	@param p3 Third vertex of the triangle.
		*/
		Triangle(Point2D p1, Point2D p2, Point2D p3) { init(p1, p2, p3); }
		
		/** Parametric constructor.
		*	@param x1 X coordinate of the first vertex of the triangle.
		*	@param y1 Y coordinate of the first vertex of the triangle.
		*	@param x2 X coordinate of the second vertex of the triangle.
		*	@param y2 Y coordinate of the second vertex of the triangle.
		*	@param x3 X coordinate of the third vertex of the triangle.
		*	@param y3 Y coordinate of the third vertex of the triangle.
		*/
		Triangle(float x1, float y1, float x2, float y2, float x3, float y3) { init(Point2D(x1, y1), Point2D(x2, y2), Point2D(x3, y3)); }

		/** Initializes the triangle.
		*	@param p1 First vertex of the triangle.
		*	@param p2 Second vertex of the triangle.
		*	@param p3 Third vertex of the triangle.
		*/
		void init(Point2D p1, Point2D p2, Point2D p3) { this->p1 = p1; this->p2 = p2; this->p3 = p3; }
	};

	struct Rectangle {
		Point2D p1, /**< Top left corner of the rectangle. */
				p2; /**< Bottom right corner of the rectangle. */

		/** Default constructor. */
		Rectangle() {}
		
		/** Parametric constructor.
		*	@param p1 Top left corner of the rectangle.
		*	@param p2 Bottom right corner of the rectangle.
		*/
		Rectangle(Point2D p1, Point2D p2) { init(p1, p2); }
		
		/** Parametric constructor.
		*	@param x1 X coordinate of the top left corner of the rectangle.
		*	@param y1 Y coordinate of the top left corner of the rectangle.
		*	@param x2 X coordinate of the bottom right corner of the rectangle.
		*	@param y2 Y coordinate of the bottom right corner of the rectangle.
		*/
		Rectangle(float x1, float y1, float x2, float y2) { init(Point2D(x1, y1), Point2D(x2, y2)); }

		/** Initializes the rectangle.
		*	@param p1 Top left corner of the rectangle.
		*	@param p2 Bottom right corner of the rectangle.
		*/
		void init(Point2D p1, Point2D p2) { this->p1 = p1; this->p2 = p2; }
	};

	struct RoundedRectangle {
		Point2D p1, /**< Top left corner of the rectangle. */
				p2; /**< Bottom right corner of the rectangle. */
		float rx, 	/**< Horizontal radius of the rounding ellipse. */
			  ry;	/**< Vertical radius of the rounding ellipse. */

		/** Default constructor. */
		RoundedRectangle() { rx = 0; ry = 0; }
		
		/** Parametric constructor.
		*	@param p1 coordinates of the top left corner.
		*	@param p2 coordinates of the bottom right corner.
		*	@param rx Horizontal radius of the rounding ellipse.
		*	@param ry Vertical radius of the rounding ellipse.
		*/
		RoundedRectangle(Point2D p1, Point2D p2, float rx, float ry) { init(p1, p2, rx, ry); }
		
		/** Parametric constructor.
		*	@param x1 X coordinate of the top left corner.
		*	@param y1 Y coordinate of the top left corner.
		*	@param x2 X coordinate of the bottom right corner.
		*	@param y2 Y coordinate of the bottom right corner.
		*	@param rx Horizontal radius of the rounding ellipse.
		*	@param ry Vertical radius of the rounding ellipse.
		*/
		RoundedRectangle(float x1, float y1, float x2, float y2, float rx, float ry) { init(Point2D(x1, y1), Point2D(x2, y2), rx, ry); }

		/** Initializes the rectangle.
		*	@param p1 coordinates of the top left corner.
		*	@param p2 coordinates of the bottom right corner.
		*	@param rx Horizontal radius of the rounding ellipse.
		*	@param ry Vertical radius of the rounding ellipse.
		*/
		void init(Point2D p1, Point2D p2, float rx, float ry) { this->p1 = p1; this->p2 = p2; this->rx = rx; this->ry = ry; }
	};

	struct Circle {
		Point2D center; /**< Center of the circle. */
		float r;		/**< Radius of the circle. */

		/** Default constructor. */
		Circle() { r = 0; }
		
		/** Parametric constructor. 
		*	@param c coordinates of the center of the circle.
		*	@param r Radius of the circle.
		*/
		Circle(Point2D center, float r) { init(center, r); }
		
		/** Parametric constructor.
		*	@param cx X coordinate of the center of the circle.
		*	@param cy Y coordinate of the center of the circle.
		*	@param r Radius of the circle.
		*/
		Circle(float cx, float cy, float r) { init(Point2D(cx, cy), r); }

		/** Initializes the circle.
		*	@param c coordinates of the center of the circle.
		*	@param r Radius of the circle.
		*/
		void init(Point2D center, float r) { this->center = center; this->r = r; }
	};

	struct Ellipse {
		Point2D center;  /**< Center of the ellipse. */
		float rx, 		/**< Horizontal radius of the ellipse. */
			  ry;		/**< Vertical radius of the ellipse. */

		/** Default constructor. */
		Ellipse() { rx = 0; ry = 0; }
		
		/** Parametric constructor. 
		*	@param c coordinates of the center of the ellipse.
		*	@param rx Horizontal radius of the ellipse.
		*	@param ry Vertical radius of the ellipse.
		*/
		Ellipse(Point2D center, float rx, float ry) { init(center, rx, ry); }
		
		/** Parametric constructor. 
		*	@param cx X coordinate of the center of the ellipse.
		*	@param cy Y coordinate of the center of the ellipse.
		*	@param rx Horizontal radius of the ellipse.
		*	@param ry Vertical radius of the ellipse.
		*/
		Ellipse(float cx, float cy, float rx, float ry) { init(Point2D(cx, cy), rx, ry); }

		/** Initializes the ellipse.
		*	@param c coordinates of the center of the ellipse.
		*	@param rx Horizontal radius of the ellipse.
		*	@param ry Vertical radius of the ellipse.
		*/
		void init(Point2D center, float rx, float ry) { this->center = center; this->rx = rx; this->ry = ry; }
	};

	struct Arc {
		Point2D center;	/**< Center of the arc. */
		float r;		/**< Radius of the arc. */
		Angle angle;	/**< Angle of the arc. */

		/** Default constructor. */
		Arc() {}
		
		/** Parametric constructor. 
		*	@param c coordinates of the center of the arc.
		*	@param r Radius of the arc.
		*	@param angle Angle of the arc.
		*/
		Arc(Point2D center, float r, Angle angle) { init(center, r, angle); }
		
		/** Parametric constructor. 
		*	@param cx X coordinate of the center of the arc.
		*	@param cy Y coordinate of the center of the arc.
		*	@param r Radius of the arc.
		*	@param angle Angle of the arc.
		*/
		Arc(float cx, float cy, float r, Angle angle) { init(Point2D(cx, cy), r, angle); }
		
		/** Parametric constructor. 
		*	@param c coordinates of the center of the arc.
		*	@param r Radius of the arc.
		*	@param start Start point of the angle.
		*	@param delta Angle increase.
		*	@param angle_conversion_type If the angle has to be converted before creating the arc, a conversion type should be specified.
		*/
		Arc(Point2D center, float r, float start, float delta, int angle_conversion_type) { init(center, r, Angle(start, delta, angle_conversion_type)); }
		
		/** Parametric constructor. 
		*	@param cx X coordinate of the center of the arc.
		*	@param cy Y coordinate of the center of the arc.
		*	@param r Radius of the arc.
		*	@param start Start point of the angle.
		*	@param delta Angle increase.
		*	@param angle_conversion_type If the angle has to be converted before creating the arc, a conversion type should be specified.
		*/
		Arc(float cx, float cy, float r, float start, float delta, int angle_conversion_type) { init(Point2D(cx, cy), r, Angle(start, delta, angle_conversion_type)); }

		/** Initializes the arc.
		*	@param c coordinates of the center of the arc.
		*	@param r Radius of the arc.
		*	@param angle Angle of the arc.
		*/
		void init(Point2D center, float r, Angle angle) { this->center = center; this->r = r; this->angle = angle; }
	};

	struct EllipticalArc {
		Point2D center;	/**< Center of the arc. */
		float rx, 		/**< Horizontal radius of the arc.*/
			  ry;		/**< Vertical radius of the arc. */
		Angle angle;	/**< Angle of the arc. */

		/** Default constructor. */
		EllipticalArc() {}
		
		/** Parametric constructor. 
		*	@param center coordinates of the center of the arc.
		*	@param rx Horizontal radius of the arc.
		*	@param ry Vertical radius of the arc.
		*	@param angle Angle of the arc.
		*/
		EllipticalArc(Point2D center, float rx, float ry, Angle angle) { init(center, rx, ry, angle); }
		
		/** Parametric constructor. 
		*	@param cx X coordinate of the center of the arc.
		*	@param cy Y coordinate of the center of the arc.
		*	@param rx Horizontal radius of the arc.
		*	@param ry Vertical radius of the arc.
		*	@param angle Angle of the arc.
		*/
		EllipticalArc(float cx, float cy, float rx, float ry, Angle angle) { init(Point2D(cx, cy), rx, ry, angle); }
		
		/** Parametric constructor.
		*	@param center coordinates of the center of the arc.
		*	@param rx Horizontal radius of the arc.
		*	@param ry Vertical radius of the arc.
		*	@param start_theta Start point of the angle.
		*	@param delta_theta Angle increase.
		*	@param angle_conversion_type If the angle has to be converted before creating the arc, a conversion type should be specified.
		*/
		EllipticalArc(Point2D center, float rx, float ry, float start, float delta, int angle_conversion_type) { init(center, rx, ry, Angle(start, delta, angle_conversion_type)); }
		
		/** Parametric constructor. 
		*	@param cx X coordinate of the center of the arc.
		*	@param cy Y coordinate of the center of the arc.
		*	@param rx Horizontal radius of the arc.
		*	@param ry Vertical radius of the arc.
		*	@param start_theta Start point of the angle.
		*	@param delta_theta Angle increase.
		*	@param angle_conversion_type If the angle has to be converted before creating the arc, a conversion type should be specified.
		*/
		EllipticalArc(float cx, float cy, float rx, float ry, float start, float delta, int angle_conversion_type) { init(Point2D(cx, cy), rx, ry, Angle(start, delta, angle_conversion_type)); }

		/** Initializes the arc.
		*	@param center coordinates of the center of the arc.
		*	@param rx Horizontal radius of the arc.
		*	@param ry Vertical radius of the arc.
		*	@param angle Angle of the arc.
		*/
		void init(Point2D center, float rx, float ry, Angle angle) { this->center = center; this->rx = rx; this->ry = ry; this->angle = angle; }
	};

	typedef Arc Pieslice; //A pie slice is basically an arc with two radii joining both ends with the center of that arc, the attributes are the same

	//The following structs doesn't use Point2D for efficiency reasons.

	struct Spline {
		float* points;	/**< Array of X and Y coordinates that defines the spline's control points.*/

		/** Default constructor. */
		Spline() { points = NULL; }
		
		/** Parametric constructor. 
		*	@param points Array of X and Y coordinates containing the spline's control points.
		*/
		Spline(const float points[8]) { init(points); }
		
		/** Copy constructor. 
		*	@param s The Spline to be copied.
		*/
		Spline(const Spline & s) { copy(s); }
		
		/** Destructor. */
		~Spline() { destroy(); }

		/** Assignment operator. 
		*	@param s The spline to be copied in the assignment.
		*/
		Spline& operator=(const Spline & s) {
			if (this != &s) {
				destroy();
				copy(s);
			}
			return *this;
		}

		/** Initializes the spline.
		*	@param points Array of X and Y coordinates containing the spline's control points.
		*/
		void init(const float points[8]) { this->points = getCopyOfArray(points, 8); }
		
		/** Copies the information of @p s into this Spline.
		*	@param s The spline to be copied.
		*/
		void copy(const Spline & s) { init(s.points); }
		
		/** Frees all dynamic memory assigned to this struct. */
		void destroy() { if (points) delete points; }
	};

	struct Polygon {
		float* points;	/**< Array of X and Y coordinates that defines the polygon's points.*/
		int num_points;	/**< Number of vertices the polygon has. */

		/** Default constructor. */
		Polygon() { points = NULL; num_points = 0; }
		
		/** Parametric constructor.
		*	@param points Array of X and Y coordinates containing the polygon's points.
		*	@param num_points Number of pairs of coordinates @p points has.
		*/
		Polygon(const float* points, int num_points) { init(points, num_points); }
		
		/** Copy constructor. 
		*	@param p The Polygon to be copied.
		*/
		Polygon(const Polygon & p) { copy(p); }
		
		/** Destructor. */
		~Polygon() { destroy(); }

		/** Assignment operator.
		*	@param p The polygon to be copied in the assignment.
		*/
		Polygon& operator=(const Polygon & p) {
			if (this != &p) {
				destroy();
				copy(p);
			}
			return *this;
		}

		/** Initializes the polygon.
		*	@param points Array of X and Y coordinates containing the polygon's points.
		*	@param num_points Number of pairs of coordinates @p points has.
		*/
		void init(const float* points, int num_points) { this->points = getCopyOfArray(points, num_points * 2); this->num_points = num_points; }
		
		/** Copies the information of @p p into this Polygon.
		*	@param p The polygon to be copied.
		*/
		void copy(const Polygon & p) { init(p.points, p.num_points); }
		
		/** Frees all dynamic memory assigned to this struct. */
		void destroy() { if (points) delete points; }
	};

	typedef Polygon Polyline; //The main difference is that a polygon joins the last point with the first, but the data stored is the same
	typedef Polyline Ribbon; //basically the same thing
	
	struct Multipolygon { //multiple polygons stored as one figure (its intended use is for polygonWithHoles() function)
		float* vertices;	/**< Array of X and Y coordinates that defines the polygons' vertices.*/
		int* vertex_counts;	/**< Number of vertices for each polygon */

		/** Default constructor. */
		Multipolygon() { vertices = NULL; vertex_counts = NULL; }
		
		/** Parametric constructor.
		*	@param vertices Array of X and Y coordinates containing the polygons' vertices.
		*	@param vertex_counts Number of vertices of each polygon in @p vertices.
		*/
		Multipolygon(const float* vertices, const int* vertex_counts) { init(vertices, vertex_counts); }
		
		/** Copy constructor. 
		*	@param mp The Multipolygon to be copied.
		*/
		Multipolygon(const Multipolygon & mp) { copy(mp); }
		
		/** Destructor. */
		~Multipolygon() { destroy(); }

		/** Assignment operator.
		*	@param mp The multipolygon to be copied in the assignment.
		*/
		Multipolygon& operator=(const Multipolygon & mp) {
			if (this != &mp) {
				destroy();
				copy(mp);
			}
			return *this;
		}

		/** Initializes the polygon.
		*	@param vertices Array of X and Y coordinates containing the polygons' vertices.
		*	@param vertex_counts Number of vertices of each polygon in @p points.
		*/
		void init(const float* vertices, const int* vertex_counts) {
			int total_vertices = 2 * intArraySum(vertex_counts);
			this->vertices = getCopyOfArray(vertices, total_vertices);
			this->vertex_counts = getCopyOfArray(vertex_counts, nElements(vertex_counts));
		}

		/** Copies the information of @p mp into this Polygon.
		*	@param mp The multipolygon to be copied.
		*/
		void copy(const Multipolygon & mp) { init(mp.vertices, mp.vertex_counts); }
		
		/** Frees all dynamic memory assigned to this struct. */
		void destroy() { if (vertices) delete vertices;  if (vertex_counts) delete vertex_counts; }
	};

}
#endif