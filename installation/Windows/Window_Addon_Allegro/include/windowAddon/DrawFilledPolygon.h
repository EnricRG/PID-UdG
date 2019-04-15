#ifndef DRAWFILLEDPOLYGON_H
#define DRAWFILLEDPOLYGON_H

#include "Drawable.h"
#include "PaintBrush.h"
#include "Figures.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of a filled polygon and represent it on a Window drawing the figure.
*/
class DLL_EXPORT DrawFilledPolygon : public Drawable
{
public:

	/** Destructor of the class
	*/
	~DrawFilledPolygon() {};

	/** Parametric constructor of the class.
	*	@param points An array of X and Y coordinates describing the vertices of the polygon.
	*	@param num_points The number of vertices (pairs of X and Y coordinates) that @p points contains.
	*	@param color Color used to draw the figure.
	*/
	DrawFilledPolygon(const float * points, int num_points, RGBColor color);

	/** Draws a filled polygon on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:

	/** Initializes the class.
	*	@param pl Figure that contains the information of the polygon.
	*	@param color Color of the figure.
	*/
	void init(const figures::Polygon & pl, RGBColor color);

	figures::Polygon polygon; 	/**< Figure containing all the information needed to draw the polygon.*/
	RGBColor color;				/**< Color of the polygon. */
};

#endif
