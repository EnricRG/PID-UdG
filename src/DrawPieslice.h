#ifndef DRAWPIESLICE_H
#define DRAWPIESLICE_H

#include "Drawable.h"
#include "PaintBrush.h"
#include "Figures.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of a pieslice and represent it on a Window drawing the figure.
*/
class DLL_EXPORT DrawPieslice : public Drawable
{
public:
	
	/** Destructor of the class
	*/
	~DrawPieslice() {};

	/** One of the parametric constructors of the class.
	*	@param cx X coordinate of the center of the pieslice.
	*	@param cy Y coordinate of the center of the pieslice.
	*	@param r Radius of the pieslice.
	*	@param a Angle of the pieslice.
	*	@param brush PaintBrush used to draw the pieslice.
	*/
	DrawPieslice(float cx, float cy, float r, Angle a, PaintBrush brush);
	
	/** One of the parametric constructors of the class.
	*	@param cx X coordinate of the center of the pieslice.
	*	@param cy Y coordinate of the center of the pieslice.
	*	@param r Radius of the pieslice.
	*	@param a Angle of the pieslice.
	*	@param color Color used to draw the pieslice.
	*	@param thickness Thickness of the pieslice.
	*/
	DrawPieslice(float cx, float cy, float r, Angle a, RGBColor color, float thickness);
	
	/** One of the parametric constructors of the class.
	*	@param c Center of the pieslice.
	*	@param r Radius of the pieslice.
	*	@param a Angle of the pieslice.
	*	@param brush PaintBrush used to draw the pieslice.
	*/
	DrawPieslice(Point2D c, float r, Angle a, PaintBrush brush);
	
	/** One of the parametric constructors of the class.
	*	@param c Center of the pieslice.
	*	@param r Radius of the pieslice.
	*	@param a Angle of the pieslice.
	*	@param color Color used to draw the pieslice.
	*	@param thickness Thickness of the pieslice.
	*/
	DrawPieslice(Point2D c, float r, Angle a, RGBColor color, float thickness);

	/** Draws a pieslice on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:

	/** Initializes the class.
	*	@param c Center of the pieslice.
	*	@param r Radius of the pieslice.
	*	@param a Angle of the pieslice.
	*	@param brush PaintBrush used to draw the pieslice.
	*/
	void init(Point2D c, float r, Angle a, PaintBrush brush);

	figures::Pieslice pieslice;	/**< Figure containing all the information needed to draw the pieslice.*/
	PaintBrush brush; 			/**< Brush that defines the color and thickness of the pieslice. */
};

#endif
