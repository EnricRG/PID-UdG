#ifndef DRAWFILLEDPIESLICE_H
#define DRAWFILLEDPIESLICE_H

#include "Drawable.h"
#include "PaintBrush.h"
#include "Figures.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of a filled pieslice and represent it on a Window drawing the figure.
*/
class DLL_EXPORT DrawFilledPieslice : public Drawable
{
public:

	/** Destructor of the class
	*/
	~DrawFilledPieslice() {};

	/** One of the parametric constructors of the class.
	*	@param cx X coordinate of the center of the pieslice.
	*	@param cy Y coordinate of the center of the pieslice.
	*	@param r Radius of the pieslice.
	*	@param a Angle of the pieslice.
	*	@param color Color used to draw the pieslice.
	*/
	DrawFilledPieslice(float cx, float cy, float r, Angle a, RGBColor color);
	
	/** One of the parametric constructors of the class.
	*	@param c Center of the pieslice.
	*	@param r Radius of the pieslice.
	*	@param a Angle of the pieslice.
	*	@param color Color used to draw the pieslice.
	*/
	DrawFilledPieslice(Point2D c, float r, Angle a, RGBColor color);

	/** Draws a filled pieslice on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:
	
	/** Initializes the class.
	*	@param c Center of the pieslice.
	*	@param r Radius of the pieslice.
	*	@param a Angle of the pieslice.
	*	@param color Color used to draw the circle.
	*/
	void init(Point2D c, float r, Angle a, RGBColor color);

	figures::Pieslice pieslice; /**< Figure containing all the information needed to draw the pieslice.*/
	RGBColor color;				/**< Color of the pieslice. */
};

#endif
