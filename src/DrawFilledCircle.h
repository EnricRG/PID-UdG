#ifndef DRAWFILLEDCIRCLE_H
#define DRAWFILLEDCIRCLE_H

#include "Drawable.h"
#include "PaintBrush.h"
#include "Figures.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of a filled circle and represent it on a Window drawing the figure.
*/
class DLL_EXPORT DrawFilledCircle : public Drawable
{
public:

	/** Destructor of the class
	*/
	~DrawFilledCircle() {};

	/** One of the parametric constructors of the class.
	*	@param cx X coordinate of the center of the circle.
	*	@param cy Y coordinate of the center of the circle.
	*	@param r Radius of the circle.
	*	@param color Color used to draw the circle.
	*/
	DrawFilledCircle(float cx, float cy, float r, RGBColor color);
	
	/** One of the parametric constructors of the class.
	*	@param c Center of the circle.
	*	@param r Radius of the circle.
	*	@param color Color used to draw the circle.
	*/
	DrawFilledCircle(Point2D c, float r, RGBColor color);

	/** Draws a filled circle on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:
	
	/** Initializes the class.
	*	@param c Center of the circle.
	*	@param r Radius of the circle.
	*	@param color Color used to draw the circle.
	*/
	void init(Point2D c, float r, RGBColor color);

	figures::Circle circle;	/**< Figure containing all the information needed to draw the circle.*/
	RGBColor color;			/**< Color of the circle. */
};

#endif
