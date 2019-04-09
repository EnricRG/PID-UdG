#ifndef DRAWRIBBON_H
#define DRAWRIBBON_H

#include "Drawable.h"
#include "PaintBrush.h"
#include "Figures.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of a ribbon and represent it on a Window drawing the figure.
*/
#ifdef _WIN32
	class DLL_EXPORT DrawRibbon : public Drawable
#else
	class DrawRibbon : public Drawable
#endif
{
public:

	/** Destructor of the class
	*/
	~DrawRibbon() {};

	/** One of the parametric constructors of the class.
	*	@param points An array of X and Y coordinates describing the points of the ribbon.
	*	@param num_points The number of vertices (pairs of X and Y coordinates) that @p points contains.
	*	@param brush PaintBrush used to draw the spline.
	*/
	DrawRibbon(const float * points, int num_points, PaintBrush brush);
	
	/** One of the parametric constructors of the class.
	*	@param points An array of X and Y coordinates describing the points of the ribbon.
	*	@param num_points The number of vertices (pairs of X and Y coordinates) that @p points contains.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line.
	*/
	DrawRibbon(const float * points, int num_points, RGBColor color, float thickness);

	/** Draws a ribbon on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:
	
	/** Initializes the class.
	*	@param r Figure that contains the information of the ribbon.
	*	@param brush PaintBrush used to draw the ribbon.
	*/
	void init(const figures::Ribbon & r, PaintBrush brush);

	figures::Ribbon ribbon;	/**< Figure containing all the information needed to draw the ribbon.*/
	PaintBrush brush;		/**< Brush that defines the color and thickness of the ribbon. */
};

#endif
