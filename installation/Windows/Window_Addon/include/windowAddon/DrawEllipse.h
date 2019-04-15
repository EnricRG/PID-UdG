#ifndef DRAWELLIPSE_H
#define DRAWELLIPSE_H

#include "Drawable.h"
#include "PaintBrush.h"
#include "Figures.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of an ellipse and represent it on a Window drawing the figure.
*/
class DLL_EXPORT DrawEllipse : public Drawable
{
public:

	/** Destructor of the class
	*/
	~DrawEllipse() {};

	/** One of the parametric constructors of the class.
	*	@param cx X coordinate of the center of the ellipse.
	*	@param cy Y coordinate of the center of the ellipse.
	*	@param rx Horizontal radius of the ellipse.
	*	@param ry Vertical radius of the ellipse.
	*	@param brush PaintBrush used to draw the ellipse.
	*/
	DrawEllipse(float cx, float cy, float rx, float ry, PaintBrush brush);
	
	/** One of the parametric constructors of the class.
	*	@param cx X coordinate of the center of the ellipse.
	*	@param cy Y coordinate of the center of the ellipse.
	*	@param rx Horizontal radius of the ellipse.
	*	@param ry Vertical radius of the ellipse.
	*	@param color Color used to draw the ellipse.
	*	@param thickness Thickness of the ellipse.
	*/
	DrawEllipse(float cx, float cy, float rx, float ry, RGBColor color, float thickness);
	
	/** One of the parametric constructors of the class.
	*	@param c Center of the ellipse.
	*	@param rx Horizontal radius of the ellipse.
	*	@param ry Vertical radius of the ellipse.
	*	@param brush PaintBrush used to draw the ellipse.
	*/
	DrawEllipse(Point2D c, float rx, float ry, PaintBrush brush);
	
	/** One of the parametric constructors of the class.
	*	@param c Center of the ellipse.
	*	@param rx Horizontal radius of the ellipse.
	*	@param ry Vertical radius of the ellipse.
	*	@param color Color used to draw the ellipse.
	*	@param thickness Thickness of the ellipse.
	*/
	DrawEllipse(Point2D c, float rx, float ry, RGBColor color, float thickness);

	/** Draws an ellipse on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:

	/** Initializes the class.
	*	@param c Center of the ellipse.
	*	@param rx Horizontal radius of the ellipse.
	*	@param ry Vertical radius of the ellipse.
	*	@param brush PaintBrush used to draw the ellipse.
	*/
	void init(Point2D c, float rx, float ry, PaintBrush brush);

	figures::Ellipse ellipse; 	/**< Figure containing all the information needed to draw the ellipse.*/
	PaintBrush brush;			/**< Brush that defines the color and thickness of the ellipse. */
};

#endif
