#ifndef DRAWRECTANGLE_H
#define DRAWRECTANGLE_H

#include "Drawable.h"
#include "PaintBrush.h"
#include "Figures.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of a rectangle and represent it on a Window drawing the figure.
*/
class DLL_EXPORT DrawRectangle : public Drawable
{
public:

	/** Destructor of the class
	*/
	~DrawRectangle() {};

	/** One of the parametric constructors of the class.
	*	@param x1 X coordinate of the top left corner.
	*	@param y1 Y coordinate of the top left corner.
	*	@param x2 X coordinate of the bottom right corner.
	*	@param y2 Y coordinate of the bottom right corner.
	*	@param brush PaintBrush used to draw the arc.
	*/
	DrawRectangle(float x1, float y1, float x2, float y2, PaintBrush brush);
	
	/** One of the parametric constructors of the class.
	*	@param x1 X coordinate of the top left corner.
	*	@param y1 Y coordinate of the top left corner.
	*	@param x2 X coordinate of the bottom right corner.
	*	@param y2 Y coordinate of the bottom right corner.
	*	@param color Color used to draw the arc.
	*	@param thickness Thickness of the arc.
	*/
	DrawRectangle(float x1, float y1, float x2, float y2, RGBColor color, float thickness);
	
	/** One of the parametric constructors of the class.
	*	@param p1 coordinates of the top left corner.
	*	@param p2 coordinates of the bottom right corner.
	*	@param brush PaintBrush used to draw the arc.
	*/
	DrawRectangle(Point2D p1, Point2D p2, PaintBrush brush);
	
	/** One of the parametric constructors of the class.
	*	@param p1 coordinates of the top left corner.
	*	@param p2 coordinates of the bottom right corner.
	*	@param color Color used to draw the arc.
	*	@param thickness Thickness of the arc.
	*/
	DrawRectangle(Point2D p1, Point2D p2, RGBColor color, float thickness);

	/** Draws a rectangle on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:

	/** Initializes the class.
	*	@param p1 coordinates of the top left corner.
	*	@param p2 coordinates of the bottom right corner.
	*	@param brush PaintBrush used to draw the arc.
	*/
	void init(Point2D p1, Point2D p2, PaintBrush brush);

	figures::Rectangle rectangle;	/**< Figure containing all the information needed to draw the rectangle.*/
	PaintBrush brush;				/**< Brush that defines the color and thickness of the rectangle. */
};

#endif
