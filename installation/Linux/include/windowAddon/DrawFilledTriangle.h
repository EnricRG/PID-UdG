#ifndef DRAWFILLEDTRIANGLE_H
#define DRAWFILLEDTRIANGLE_H

#include "Drawable.h"
#include "RGBColor.h"
#include "Figures.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of a filled triangle and represent it on a Window drawing the figure.
*/
#ifdef _WIN32
	class DLL_EXPORT DrawFilledTriangle : public Drawable
#else
	class DrawFilledTriangle : public Drawable
#endif
{
public:
	
	/** Destructor of the class
	*/
	~DrawFilledTriangle() {};

	/** One of the parametric constructors of the class.
	*	@param x1 X coordinate of the first point.
	*	@param y1 Y coordinate of the first point.
	*	@param x2 X coordinate of the second point.
	*	@param y2 Y coordinate of the second point.
	*	@param x3 X coordinate of the third point.
	*	@param y3 Y coordinate of the third point.
	*	@param color Color used to draw the triangle.
	*/
	DrawFilledTriangle(float x1, float y1, float x2, float y2, float x3, float y3, RGBColor color);
	
	/** One of the parametric constructors of the class.
	*	@param p1 coordinates of the first point.
	*	@param p2 coordinates of the second point.
	*	@param p3 coordinates of the third point.
	*	@param color Color used to draw the triangle.
	*/
	DrawFilledTriangle(Point2D p1, Point2D p2, Point2D p3, RGBColor color);

	/** Draws a filled triangle on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:

	/** Initializes the class.
	*	@param p1 coordinates of the first point.
	*	@param p2 coordinates of the second point.
	*	@param p3 coordinates of the third point.
	*	@param color Color used to draw the triangle.
	*/
	void init(Point2D p1, Point2D p2, Point2D p3, RGBColor color);

	figures::Triangle triangle;	/**< Figure containing all the information needed to draw the triangle.*/
	RGBColor color;				/**< Color of the triangle. */
};

#endif

