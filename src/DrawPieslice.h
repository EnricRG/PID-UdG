#ifndef DRAWPIESLICE_H
#define DRAWPIESLICE_H

#include "Drawable.h"
#include "PaintBrush.h"
#include "Figures.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of a pie slice and represent it on a Window drawing the figure.
*/
class DLL_EXPORT DrawPieslice : public Drawable
{
public:
	
	/** Destructor of the class
	*/
	~DrawPieslice() {};

	/** One of the parametric constructors of the class.
	*	@param cx X coordinate of the center of the pie slice.
	*	@param cy Y coordinate of the center of the pie slice.
	*	@param r Radius of the pie slice.
	*	@param a Angle of the pie slice.
	*	@param brush PaintBrush used to draw the pie slice.
	*/
	DrawPieslice(float cx, float cy, float r, Angle a, PaintBrush brush);
	
	/** One of the parametric constructors of the class.
	*	@param cx X coordinate of the center of the pie slice.
	*	@param cy Y coordinate of the center of the pie slice.
	*	@param r Radius of the pie slice.
	*	@param a Angle of the pie slice.
	*	@param color Color used to draw the pie slice.
	*	@param thickness Thickness of the pie slice.
	*/
	DrawPieslice(float cx, float cy, float r, Angle a, RGBColor color, float thickness);
	
	/** One of the parametric constructors of the class.
	*	@param c Center of the pie slice.
	*	@param r Radius of the pie slice.
	*	@param a Angle of the pie slice.
	*	@param brush PaintBrush used to draw the pie slice.
	*/
	DrawPieslice(Point2D c, float r, Angle a, PaintBrush brush);
	
	/** One of the parametric constructors of the class.
	*	@param c Center of the pie slice.
	*	@param r Radius of the pie slice.
	*	@param a Angle of the pie slice.
	*	@param color Color used to draw the pie slice.
	*	@param thickness Thickness of the pie slice.
	*/
	DrawPieslice(Point2D c, float r, Angle a, RGBColor color, float thickness);

	/** Draws a pie slice on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:

	/** Initializes the class.
	*	@param c Center of the pie slice.
	*	@param r Radius of the pie slice.
	*	@param a Angle of the pie slice.
	*	@param brush PaintBrush used to draw the pie slice.
	*/
	void init(Point2D c, float r, Angle a, PaintBrush brush);

	figures::Pieslice pieslice;	/**< Figure containing all the information needed to draw the pie slice.*/
	PaintBrush brush; 			/**< Brush that defines the color and thickness of the pie slice. */
};

#endif
