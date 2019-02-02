#ifndef DRAWLINE_H
#define DRAWLINE_H

#include "Drawable.h"
#include "PaintBrush.h"
#include "Point2D.h"

/** @brief Implementation of Drawable interface
*	This class is capable of storing the information of a line and represent it on a Window drawing the figure.
*/
class DLL_EXPORT DrawLine : public Drawable
{
public:

	/** Destructor of the class
	*/
	~DrawLine() {};

	/** One of the parametric constructors of the class.
	*	@param x1 X coordinate of the first point.
	*	@param y1 Y coordinate of the first point.
	*	@param x2 X coordinate of the second point.
	*	@param y2 Y coordinate of the second point.
	*	@param brush PaintBrush used to draw the arc.
	*/
	DrawLine(float x1, float y1, float x2, float y2, PaintBrush brush);
	
	/** One of the parametric constructors of the class.
	*	@param x1 X coordinate of the first point.
	*	@param y1 Y coordinate of the first point.
	*	@param x2 X coordinate of the second point.
	*	@param y2 Y coordinate of the second point.
	*	@param color Color used to draw the pixel.
	*	@param thickness Thickness of the line.
	*/
	DrawLine(float x1, float y1, float x2, float y2, RGBColor color, float thickness);
	
	/** One of the parametric constructors of the class.
	*	@param p1 coordinates of the first point.
	*	@param p2 coordinates of the second point.
	*	@param brush PaintBrush used to draw the arc.
	*/
	DrawLine(Point2D p1, Point2D p2, PaintBrush brush);
	
	/** One of the parametric constructors of the class.
	*	@param p1 coordinates of the first point.
	*	@param p2 coordinates of the second point.
	*	@param color Color used to draw the pixel.
	*	@param thickness Thickness of the line.
	*/
	DrawLine(Point2D p1, Point2D p2, RGBColor color, float thickness);

	/** Draws a line on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:

	/** Initializes the class.
	*	@param p1 coordinates of the first point.
	*	@param p2 coordinates of the second point.
	*	@param brush PaintBrush used to draw the arc.
	*/
	void init(Point2D p1, Point2D p2, PaintBrush brush);

	Point2D p1, 		/**< Start point of the line*/
			p2; 		/**< End point of the line*/
	PaintBrush brush;	/**< Brush that defines the color and thickness of the line */
};

#endif
