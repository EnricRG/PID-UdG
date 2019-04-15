#ifndef DRAWIMAGE_H
#define DRAWIMAGE_H

#include "Drawable.h"
#include "Image.h"
#include "Point2D.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of an Image and represent it on a Window drawing it.
*/
class DLL_EXPORT DrawImage : public Drawable
{
public:

	/** Destructor of the class
	*/
	~DrawImage() {};

	/** One of the parametric constructors of the class.
	*	@param i Image to be drawn.
	*	@param p The point where bottom left corner will be drawn.
	*	@param flags Flags for the bitmap drawing.
	*/
	DrawImage(const Image & i, Point2D p, int flags);
	
	/** One of the parametric constructors of the class.
	*	@param i Image to be drawn.
	*	@param x X coordinate of the point where bottom left corner will be drawn.
	*	@param y Y coordinate of the point where bottom left corner will be drawn.
	*	@param flags Flags for the bitmap drawing.
	*/
	DrawImage(const Image & i, float x, float y, int flags);

	/** Draws an Image on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:

	/** Initializes the class.
	*	@param i Image to be drawn.
	*	@param p The point where bottom left corner will be drawn.
	*	@param flags Flags for the bitmap drawing.
	*/
	void init(Image i, Point2D p, int flags);

	Point2D p;		/**< The point where bottom left corner will be.*/
	Image image;	/**< The Image.*/
	int flags;		/**< Flags for the bitmap drawing.*/
};

#endif
