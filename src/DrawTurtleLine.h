#ifndef DRAWTURTLELINE_H
#define DRAWTURTLELINE_H

#include "Drawable.h"
#include "PaintBrush.h"
#include "Point2D.h"

/** @brief Implementation of Drawable interface
*	This class is capable of storing the information of a Turtle line and represent it on a Window drawing the figure.
*/
class DrawTurtleLine : public Drawable
{
public:

	/** Destructor of the class
	*/
	~DrawTurtleLine() {};

	/** One of the parametric constructors of the class.
	*	@param x1 X coordinate of the first point.
	*	@param y1 Y coordinate of the first point.
	*	@param x2 X coordinate of the second point.
	*	@param y2 Y coordinate of the second point.
	*	@param brush PaintBrush used to draw the arc.
	*	@param showing_cursor Indictes if the turtle using this function was visible or not.
	*/
	DrawTurtleLine(float x1, float y1, float x2, float y2, PaintBrush brush, bool showing_cursor);
	
	/** One of the parametric constructors of the class.
	*	@param x1 X coordinate of the first point.
	*	@param y1 Y coordinate of the first point.
	*	@param x2 X coordinate of the second point.
	*	@param y2 Y coordinate of the second point.
	*	@param color Color used to draw the pixel.
	*	@param thickness Thickness of the line.
	*	@param showing_cursor Indictes if the turtle using this function was visible or not.
	*/
	DrawTurtleLine(float x1, float y1, float x2, float y2, RGBColor color, float thickness, bool showing_cursor);
	
	/** One of the parametric constructors of the class.
	*	@param p1 coordinates of the first point.
	*	@param p2 coordinates of the second point.
	*	@param brush PaintBrush used to draw the arc.
	*	@param showing_cursor Indictes if the turtle using this function was visible or not.
	*/
	DrawTurtleLine(Point2D p1, Point2D p2, PaintBrush brush, bool showing_cursor);
	
	/** One of the parametric constructors of the class.
	*	@param p1 coordinates of the first point.
	*	@param p2 coordinates of the second point.
	*	@param color Color used to draw the pixel.
	*	@param thickness Thickness of the line.
	*	@param showing_cursor Indictes if the turtle using this function was visible or not.
	*/
	DrawTurtleLine(Point2D p1, Point2D p2, RGBColor color, float thickness, bool showing_cursor);

	/** Draws a Turtle line on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:

	/** Initializes the class.
	*	@param p1 coordinates of the first point.
	*	@param p2 coordinates of the second point.
	*	@param brush PaintBrush used to draw the arc.
	*	@param showing_cursor Indictes if the turtle using this function is visible or not.
	*/
	void init(Point2D p1, Point2D p2, PaintBrush brush, bool showing_cursor);

	Point2D p1, 		/**< Start point of the line*/
			p2; 		/**< End point of the line*/
	PaintBrush brush; 	/**< Brush that defines the color and thickness of the line */
	bool showing_cursor;/**< Indictes if the turtle using this function was visible or not.*/
};

#endif