#ifndef DRAWPOLYLINE_H
#define DRAWPOLYLINE_H

#include "Drawable.h"
#include "PaintBrush.h"
#include "Figures.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of a polyline and represent it on a Window drawing the figure.
*/
#ifdef _WIN32
	class DLL_EXPORT DrawPolyline : public Drawable
#else
	class DrawPolyline : public Drawable
#endif
{
public:

	/** Destructor of the class
	*/
	~DrawPolyline() {};

	/** One of the parametric constructors of the class.
	*	@param points An array of X and Y coordinates describing the points of the polyline.
	*	@param num_points The number of vertices (pairs of X and Y coordinates) that @p points contains.
	*	@param brush PaintBrush used to draw the polyline.
	*/
	DrawPolyline(const float * points, int num_points, PaintBrush brush);
	
	/** One of the parametric constructors of the class.
	*	@param points An array of X and Y coordinates describing the points of the polyline.
	*	@param num_points The number of vertices (pairs of X and Y coordinates) that @p points contains.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line.
	*/
	DrawPolyline(const float * points, int num_points, RGBColor color, float thickness);

	/** Draws a polyline on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:

	/** Initializes the class.
	*	@param pl Figure that contains the information of the polyline.
	*	@param brush PaintBrush used to draw the polyline.
	*/
	void init(const figures::Polyline & pl, PaintBrush brush);

	figures::Polyline polyline;	/**< Figure containing all the information needed to draw the polyline.*/
	PaintBrush brush;			/**< Brush that defines the color and thickness of the polyline. */
};

#endif
