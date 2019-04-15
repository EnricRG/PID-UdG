#ifndef DRAWCIRCLE_H
#define DRAWCIRCLE_H

#include "Drawable.h"
#include "PaintBrush.h"
#include "Figures.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of a circle and represent it on a Window drawing the figure.
*/
class DLL_EXPORT DrawCircle : public Drawable
{
public:

	/** Destructor of the class
	*/
	~DrawCircle() {};

	/** One of the parametric constructors of the class.
	*	@param cx X coordinate of the center of the circle.
	*	@param cy Y coordinate of the center of the circle.
	*	@param r Radius of the circle.
	*	@param brush PaintBrush used to draw the circle.
	*/
	DrawCircle(float cx, float cy, float r, PaintBrush brush);
	
	/** One of the parametric constructors of the class.
	*	@param cx X coordinate of the center of the circle.
	*	@param cy Y coordinate of the center of the circle.
	*	@param r Radius of the circle.
	*	@param color Color used to draw the circle.
	*	@param thickness Thickness of the circle.
	*/
	DrawCircle(float cx, float cy, float r, RGBColor color, float thickness);
	
	/** One of the parametric constructors of the class.
	*	@param c Center of the circle.
	*	@param r Radius of the circle.
	*	@param brush PaintBrush used to draw the circle.
	*/
	DrawCircle(Point2D c, float r, PaintBrush brush);
	
	/** One of the parametric constructors of the class.
	*	@param c Center of the circle.
	*	@param r Radius of the circle.
	*	@param color Color used to draw the circle.
	*	@param thickness Thickness of the circle.
	*/
	DrawCircle(Point2D c, float r, RGBColor color, float thickness);

	/** Draws a circle on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:

	/** Initializes the class.
	*	@param c Center of the circle.
	*	@param r Radius of the circle.
	*	@param brush PaintBrush used to draw the circle.
	*/
	void init(Point2D c, float r, PaintBrush brush);

	figures::Circle circle;	/**< Figure containing all the information needed to draw the circle.*/
	PaintBrush brush; 		/**< Brush that defines the color and thickness of the circle. */
};

#endif
