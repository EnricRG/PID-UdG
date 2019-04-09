#ifndef DRAWTRIANGLE_H
#define DRAWTRIANGLE_H

#include "Drawable.h"
#include "PaintBrush.h"
#include "Figures.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of a triangle and represent it on a Window drawing the figure.
*/
#ifdef _WIN32
	class DLL_EXPORT DrawTriangle : public Drawable
#else
	class DrawTriangle : public Drawable
#endif
{
public:

	/** Destructor of the class
	*/
	~DrawTriangle() {};

	/** One of the parametric constructors of the class.
	*	@param x1 X coordinate of the first point.
	*	@param y1 Y coordinate of the first point.
	*	@param x2 X coordinate of the second point.
	*	@param y2 Y coordinate of the second point.
	*	@param x3 X coordinate of the third point.
	*	@param y3 Y coordinate of the third point.
	*	@param brush PaintBrush used to draw the triangle.
	*/
	DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, PaintBrush brush);
	
	/** One of the parametric constructors of the class.
	*	@param x1 X coordinate of the first point.
	*	@param y1 Y coordinate of the first point.
	*	@param x2 X coordinate of the second point.
	*	@param y2 Y coordinate of the second point.
	*	@param x3 X coordinate of the third point.
	*	@param y3 Y coordinate of the third point.
	*	@param color Color used to draw the triangle.
	*	@param thickness Thickness of the triangle. 
	*/
	DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, RGBColor color, float thickness);
	
	/** One of the parametric constructors of the class.
	*	@param p1 coordinates of the first point.
	*	@param p2 coordinates of the second point.
	*	@param p3 coordinates of the third point.
	*	@param brush PaintBrush used to draw the triangle.
	*/
	DrawTriangle(Point2D p1, Point2D p2, Point2D p3, PaintBrush brush);
	
	/** One of the parametric constructors of the class.
	*	@param p1 coordinates of the first point.
	*	@param p2 coordinates of the second point.
	*	@param p3 coordinates of the third point.
	*	@param color Color used to draw the triangle.
	*	@param thickness Thickness of the triangle.
	*/
	DrawTriangle(Point2D p1, Point2D p2, Point2D p3, RGBColor color, float thickness);

	/** Draws a triangle on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:

	/** Initializes the class.
	*	@param p1 coordinates of the first point.
	*	@param p2 coordinates of the second point.
	*	@param p3 coordinates of the third point.
	*	@param brush PaintBrush used to draw the triangle.
	*/
	void init(Point2D p1, Point2D p2, Point2D p3, PaintBrush brush);

	figures::Triangle triangle;	/**< Figure containing all the information needed to draw the triangle.*/
	PaintBrush brush;			/**< Brush that defines the color and thickness of the triangle. */
};

#endif
