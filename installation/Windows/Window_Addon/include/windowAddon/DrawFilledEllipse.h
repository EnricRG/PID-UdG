#ifndef DRAWFILLEDELLIPSE_H
#define DRAWFILLEDELLIPSE_H

#include "Drawable.h"
#include "PaintBrush.h"
#include "Figures.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of a filled ellipse and represent it on a Window drawing the figure.
*/
class DLL_EXPORT DrawFilledEllipse : public Drawable
{
public:

	/** Destructor of the class
	*/
	~DrawFilledEllipse() {};

	/** One of the parametric constructors of the class.
	*	@param cx X coordinate of the center of the ellipse.
	*	@param cy Y coordinate of the center of the ellipse.
	*	@param rx Horizontal radius of the ellipse.
	*	@param ry Vertical radius of the ellipse.
	*	@param color Color used to draw the ellipse.
	*/
	DrawFilledEllipse(float cx, float cy, float rx, float ry, RGBColor color);
	
	/** One of the parametric constructors of the class.
	*	@param c Center of the ellipse.
	*	@param rx Horizontal radius of the ellipse.
	*	@param ry Vertical radius of the ellipse.
	*	@param color Color used to draw the ellipse.
	*/
	DrawFilledEllipse(Point2D c, float rx, float ry, RGBColor color);

	/** Draws a filled ellipse on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:

	/** Initializes the class.
	*	@param c Center of the ellipse.
	*	@param rx Horizontal radius of the ellipse.
	*	@param ry Vertical radius of the ellipse.
	*	@param color Color used to draw the circle.
	*/
	void init(Point2D c, float rx, float ry, RGBColor color);

	figures::Ellipse ellipse; 	/**< Figure containing all the information needed to draw the ellipse.*/
	RGBColor color;				/**< Color of the ellipse. */
};

#endif
