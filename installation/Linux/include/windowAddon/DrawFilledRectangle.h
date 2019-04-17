#ifndef DRAWFILLEDRECTANGLE_H
#define DRAWFILLEDRECTANGLE_H

#include "Drawable.h"
#include "PaintBrush.h"
#include "Figures.h"


/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of a filled rectangle and represent it on a Window drawing the figure.
*/
#ifdef _WIN32
	class DLL_EXPORT DrawFilledRectangle : public Drawable
#else
	class DrawFilledRectangle : public Drawable
#endif
{
public:

	/** Destructor of the class
	*/
	~DrawFilledRectangle() {};

	/** One of the parametric constructors of the class.
	*	@param x1 X coordinate of the top left corner.
	*	@param y1 Y coordinate of the top left corner.
	*	@param x2 X coordinate of the bottom right corner.
	*	@param y2 Y coordinate of the bottom right corner.
	*	@param color Color used to draw the figure.
	*/
	DrawFilledRectangle(float x1, float y1, float x2, float y2, RGBColor color);
	/** One of the parametric constructors of the class.
	*	@param p1 coordinates of the top left corner.
	*	@param p2 coordinates of the bottom right corner.
	*	@param color Color used to draw the figure.
	*/
	DrawFilledRectangle(Point2D p1, Point2D p2, RGBColor color);

	/** Draws a filled rectangle on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:

	/** Initializes the class.
	*	@param p1 coordinates of the top left corner.
	*	@param p2 coordinates of the bottom right corner.
	*	@param color Color used to draw the figure.
	*/
	void init(Point2D p1, Point2D p2, RGBColor color);

	figures::Rectangle rectangle;	/**< Figure containing all the information needed to draw the rectangle.*/
	RGBColor color;					/**< Color of the polygon. */
};

#endif
