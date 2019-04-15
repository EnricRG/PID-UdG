#ifndef DRAWFILLEDROUNDEDRECTANGLE_H
#define DRAWFILLEDROUNDEDRECTANGLE_H

#include "Drawable.h"
#include "PaintBrush.h"
#include "Figures.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of a filled rounded rectangle and represent it on a Window drawing the figure.
*/
#ifdef _WIN32
	class DLL_EXPORT DrawFilledRoundedRectangle : public Drawable
#else
	class DrawFilledRoundedRectangle : public Drawable
#endif
{
public:
	
	/** Destructor of the class
	*/
	~DrawFilledRoundedRectangle() {};
	
	/** One of the parametric constructors of the class.
	*	@param x1 X coordinate of the top left corner.
	*	@param y1 Y coordinate of the top left corner.
	*	@param x2 X coordinate of the bottom right corner.
	*	@param y2 Y coordinate of the bottom right corner.
	*	@param rx Horizontal radius of the rounding ellipse.
	*	@param ry Vertical radius of the rounding ellipse.
	*	@param color Color used to draw the figure.
	*/
	DrawFilledRoundedRectangle(float x1, float y1, float x2, float y2, float rx, float ry, RGBColor color);
	
	/** One of the parametric constructors of the class.
	*	@param p1 coordinates of the top left corner.
	*	@param p2 coordinates of the bottom right corner.
	*	@param rx Horizontal radius of the rounding ellipse.
	*	@param ry Vertical radius of the rounding ellipse.
	*	@param color Color used to draw the figure.
	*/
	DrawFilledRoundedRectangle(Point2D p1, Point2D p2, float rx, float ry, RGBColor color);

	/** Draws a filled rounded rectangle on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:

	/** Initializes the class.
	*	@param p1 coordinates of the top left corner.
	*	@param p2 coordinates of the bottom right corner.
	*	@param rx Horizontal radius of the rounding ellipse.
	*	@param ry Vertical radius of the rounding ellipse.
	*	@param color Color used to draw the figure.
	*/
	void init(Point2D p1, Point2D p2, float rx, float ry, RGBColor color);

	figures::Rectangle rectangle;	/**< Figure containing all the information needed to draw the rectangle.*/
	float rx, 						/**< Horizontal radius of the rounding ellipse. */
		  ry;						/**< Vertical radius of the rounding ellipse.*/
	RGBColor color;					/**< Color of the rectangle.*/
};

#endif
