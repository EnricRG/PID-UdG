#ifndef DRAWARC_H
#define DRAWARC_H

#include "Drawable.h"
#include "PaintBrush.h"
#include "Figures.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of an arc and represent it on a Window drawing the figure.
*/
#ifdef _WIN32
	class DLL_EXPORT DrawArc : public Drawable
#else
	class DrawArc : public Drawable
#endif
{
public:

	/** Destructor of the class
	*/
	~DrawArc() {};
	
	/** One of the parametric constructors of the class.
	*	@param cx X coordinate of the center of the arc.
	*	@param cy Y coordinate of the center of the arc.
	*	@param r Radius of the arc.
	*	@param a Angle of the arc.
	*	@param brush PaintBrush used to draw the arc.
	*/
	DrawArc(float cx, float cy, float r, Angle a, PaintBrush brush);
	
	/** One of the parametric constructors of the class.
	*	@param cx X coordinate of the center of the arc.
	*	@param cy Y coordinate of the center of the arc.
	*	@param r Radius of the arc.
	*	@param a Angle of the arc.
	*	@param color Color used to draw the arc.
	*	@param thickness Thickness of the arc.
	*/
	DrawArc(float cx, float cy, float r, Angle a, RGBColor color, float thickness);
	
	/** One of the parametric constructors of the class.
	*	@param c Center of the arc.
	*	@param r Radius of the arc.
	*	@param a Angle of the arc.
	*	@param brush PaintBrush used to draw the arc.
	*/
	DrawArc(Point2D c, float r, Angle a, PaintBrush brush);
	
	/** One of the parametric constructors of the class.
	*	@param c Center of the arc.
	*	@param r Radius of the arc.
	*	@param a Angle of the arc.
	*	@param color Color used to draw the arc.
	*	@param thickness Thickness of the arc.
	*/
	DrawArc(Point2D c, float r, Angle a, RGBColor color, float thickness);

	/** Draws an arc on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:

	/** Initializes the class.
	*	@param c Center of the arc.
	*	@param r Radius of the arc.
	*	@param a Angle of the arc.
	*	@param brush PaintBrush used to draw the arc.
	*/
	void init(Point2D c, float r, Angle a, PaintBrush brush);

	figures::Arc arc; /**< Figure containing all the information needed to draw the arc.*/
	PaintBrush brush; /**< Brush that defines the color and thickness of the arc. */
};

#endif
