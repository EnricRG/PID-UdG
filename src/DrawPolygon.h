#ifndef DRAWPOLYGON_H
#define DRAWPOLYGON_H

#include "Drawable.h"
#include "PaintBrush.h"
#include "Figures.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of a polygon and represent it on a Window drawing the figure.
*/
class DLL_EXPORT DrawPolygon : public Drawable
{
public:

	/** Destructor of the class
	*/
	~DrawPolygon() {};

	/** One of the parametric constructors of the class.
	*	@param points An array of X and Y coordinates descriving the vertices of the polygon.
	*	@param num_points The number of vertices (pairs of X and Y coordinates) that @p points contains.
	*	@param brush PaintBrush used to draw the arc.
	*/
	DrawPolygon(const float * points, int num_points, PaintBrush brush);
	
	/** One of the parametric constructors of the class.
	*	@param points An array of X and Y coordinates descriving the vertices of the polygon.
	*	@param num_points The number of vertices (pairs of X and Y coordinates) that @p points contains.
	*	@param color Color used to draw the arc.
	*	@param thickness Thickness of the arc.
	*/
	DrawPolygon(const float * points, int num_points, RGBColor color, float thickness);

	/** Draws a polygon on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:

	/** Initializes the class.
	*	@param pl Figure that contains the information of the polygon.
	*	@param brush PaintBrush used to draw the polygon.
	*/
	void init(const figures::Polygon & pl, PaintBrush brush);

	figures::Polygon polygon;	/**< Figure containing all the information needed to draw the polygon.*/
	PaintBrush brush;			/**< Brush that defines the color and thickness of the polygon */
};

#endif
