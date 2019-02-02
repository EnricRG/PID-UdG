#ifndef DRAWELLIPTICALARC_H
#define DRAWELLIPTICALARC_H

#include "Drawable.h"
#include "PaintBrush.h"
#include "Figures.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of an elliptical arc and represent it on a Window drawing the figure.
*/
class DLL_EXPORT DrawEllipticalArc : public Drawable
{
public:

	/** Destructor of the class
	*/
	~DrawEllipticalArc() {};

	/** One of the parametric constructors of the class.
	*	@param cx X coordinate of the center of the arc.
	*	@param cy Y coordinate of the center of the arc.
	*	@param rx Horizontal radius of the arc.
	*	@param ry Vertical radius of the arc.
	*	@param a Angle of the arc.
	*	@param brush PaintBrush used to draw the arc.
	*/
	DrawEllipticalArc(float cx, float cy, float rx, float ry, Angle a, PaintBrush brush);
	
	/** One of the parametric constructors of the class.
	*	@param cx X coordinate of the center of the arc.
	*	@param cy Y coordinate of the center of the arc.
	*	@param rx Horizontal radius of the arc.
	*	@param ry Vertical radius of the arc.
	*	@param a Angle of the arc.
	*	@param color Color used to draw the arc.
	*	@param thickness Thickness of the arc.
	*/
	DrawEllipticalArc(float cx, float cy, float rx, float ry, Angle a, RGBColor color, float thickness);
	
	/** One of the parametric constructors of the class.
	*	@param c Center of the arc.
	*	@param rx Horizontal radius of the arc.
	*	@param ry Vertical radius of the arc.
	*	@param a Angle of the arc.
	*	@param brush PaintBrush used to draw the arc.
	*/
	DrawEllipticalArc(Point2D c, float rx, float ry, Angle a, PaintBrush brush);
	
	/** One of the parametric constructors of the class.
	*	@param c Center of the arc.
	*	@param rx Horizontal radius of the arc.
	*	@param ry Vertical radius of the arc.
	*	@param a Angle of the arc.
	*	@param color Color used to draw the arc.
	*	@param thickness Thickness of the arc.
	*/
	DrawEllipticalArc(Point2D c, float rx, float ry, Angle a, RGBColor color, float thickness);

	/** Draws an elliptical arc on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:

	/** Initializes the class.
	*	@param c Center of the arc.
	*	@param rx Horizontal radius of the arc.
	*	@param ry Vertical radius of the arc.
	*	@param a Angle of the arc.
	*	@param brush PaintBrush used to draw the arc.
	*/
	void init(Point2D c, float rx, float ry, Angle a, PaintBrush brush);

	figures::EllipticalArc arc;	/**< Figure containing all the information needed to draw the elliptical arc.*/
	PaintBrush brush;			/**< Brush that defines the color and thickness of the elliptical arc. */
};

#endif
