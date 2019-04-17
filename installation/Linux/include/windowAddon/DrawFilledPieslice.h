#ifndef DRAWFILLEDPIESLICE_H
#define DRAWFILLEDPIESLICE_H

#include "Drawable.h"
#include "PaintBrush.h"
#include "Figures.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of a filled pie slice and represent it on a Window drawing the figure.
*/
#ifdef _WIN32
	class DLL_EXPORT DrawFilledPieslice : public Drawable
#else
	class DrawFilledPieslice : public Drawable
#endif
{
public:

	/** Destructor of the class
	*/
	~DrawFilledPieslice() {};

	/** One of the parametric constructors of the class.
	*	@param cx X coordinate of the center of the pie slice.
	*	@param cy Y coordinate of the center of the pie slice.
	*	@param r Radius of the pie slice.
	*	@param a Angle of the pie slice.
	*	@param color Color used to draw the pie slice.
	*/
	DrawFilledPieslice(float cx, float cy, float r, Angle a, RGBColor color);
	
	/** One of the parametric constructors of the class.
	*	@param c Center of the pie slice.
	*	@param r Radius of the pie slice.
	*	@param a Angle of the pie slice.
	*	@param color Color used to draw the pie slice.
	*/
	DrawFilledPieslice(Point2D c, float r, Angle a, RGBColor color);

	/** Draws a filled pie slice on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:
	
	/** Initializes the class.
	*	@param c Center of the pie slice.
	*	@param r Radius of the pie slice.
	*	@param a Angle of the pie slice.
	*	@param color Color used to draw the circle.
	*/
	void init(Point2D c, float r, Angle a, RGBColor color);

	figures::Pieslice pieslice; /**< Figure containing all the information needed to draw the pie slice.*/
	RGBColor color;				/**< Color of the pie slice. */
};

#endif
