#ifndef DRAWFILLEDPOLYGONWITHHOLES_H
#define DRAWFILLEDPOLYGONWITHHOLES_H

#include "Drawable.h"
#include "PaintBrush.h"
#include "Figures.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of a filled polygon with holes and represent it on a Window drawing the figure.
*/
#ifdef _WIN32
	class DLL_EXPORT DrawFilledPolygonWithHoles : public Drawable
#else
	class DrawFilledPolygonWithHoles : public Drawable
#endif
{
public:

	/** Destructor of the class
	*/
	~DrawFilledPolygonWithHoles() {};

	/** Parametric constructor of the class
	*	@param points An array of X and Y coordinates describing the vertices of the polygon.
	*	@param vertex_counts The number of vertices (pairs of X and Y coordinates) that <EM>vertices</EM> contains.
	*	@param color Color used to draw the figure.
	*/
	DrawFilledPolygonWithHoles(const float * points, const int * vertex_counts, RGBColor color);

	/** Draws a filled polygon with holes on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:

	/** Initializes the class.
	*	@param pl Figure that contains the information of the polygon.
	*	@param color Color of the figure.
	*/
	void init(const figures::Multipolygon & pl, RGBColor color);

	figures::Multipolygon multiPolygon;	/**< Figure containing all the information needed to draw the polygon.*/
	RGBColor color;						/**< Color of the polygon. */
};

#endif
