#ifndef DRAWPIXEL_H
#define DRAWPIXEL_H

#include "Drawable.h"
#include "PaintBrush.h"
#include "Point2D.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of a pixel and represent it on a Window drawing the figure.
*/
#ifdef _WIN32
	class DLL_EXPORT DrawPixel : public Drawable
#else
	class DrawPixel : public Drawable
#endif
{
public:

	/** Destructor of the class
	*/
	~DrawPixel() {};

	/** One of the parametric constructors of the class.
	*	@param x X coordinate of the pixel.
	*	@param y Y coordinate of the pixel.
	*	@param color Color used to draw the figure.
	*/
	DrawPixel(float x, float y, RGBColor color);
	
	/** One of the parametric constructors of the class.
	*	@param p coordinates of the pixel.
	*	@param color Color used to draw the figure.
	*/
	DrawPixel(Point2D p, RGBColor color);

	/** Draws a filled polygon with holes on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:

	/** Initializes the class.
	*	@param p coordinates of the pixel
	*	@param color Color used to draw the figure.
	*/
	void init(Point2D p, RGBColor color);

	Point2D p; 		/**< Pixel position on the screen */
	RGBColor color; /**< Color of the pixel */
};

#endif
