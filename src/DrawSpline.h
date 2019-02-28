#ifndef DRAWSPLINE_H
#define DRAWSPLINE_H

#include "Drawable.h"
#include "PaintBrush.h"
#include "Figures.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of a spline and represent it on a Window drawing the figure.
*/
class DLL_EXPORT DrawSpline : public Drawable
{
public:

	/** Destructor of the class
	*/
	~DrawSpline() {};

	/** One of the parametric constructors of the class.
	*	@param points An array of X and Y coordinates describing the points of the spline.
	*	@param brush PaintBrush used to draw the spline.
	*/
	DrawSpline(float * points, PaintBrush brush);
	
	/** One of the parametric constructors of the class.
	*	@param points An array of X and Y coordinates describing the points of the spline.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line.
	*/
	DrawSpline(float * points, RGBColor color, float thickness);

	/** Draws a spline on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:

	/** Initializes the class.
	*	@param s Figure that contains the information of the spline.
	*	@param brush PaintBrush used to draw the spline.
	*/
	void init(const figures::Spline & s, PaintBrush brush);

	figures::Spline spline;	/**< Figure containing all the information needed to draw the spline.*/
	PaintBrush brush;		/**< Brush that defines the color and thickness of the spline. */
};

#endif
