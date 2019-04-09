#ifndef DRAWROTATEDIMAGE_H
#define DRAWROTATEDIMAGE_H

#include "Drawable.h"
#include "Image.h"
#include "Point2D.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information of a rotated Image and represent it on a Window drawing it.
*/
#ifdef _WIN32
	class DLL_EXPORT DrawRotatedImage : public Drawable
#else
	class DrawRotatedImage : public Drawable
#endif
{
public:

	/** Destructor of the class
	*/
	~DrawRotatedImage() {};

	/** One of the parametric constructors of the class.
	*	@param i Image to be drawn.
	*	@param c The rotation point (relative to the image).
	*	@param d The point where bottom left corner will be drawn.
	*	@param angle Rotation angle.
	*	@param flags Flags for the bitmap drawing.
	*/
	DrawRotatedImage(const Image & i, Point2D c, Point2D d, float angle, int flags);
	
	/** One of the parametric constructors of the class.
	*	@param i Image to be drawn.
	*	@param cx X coordinate of the rotation point (relative to the image).
	*	@param cy Y coordinate of the rotation point (relative to the image).
	*	@param dx X coordinate of the point where bottom left corner will be drawn.
	*	@param dy Y coordinate of the point where bottom left corner will be drawn.
	*	@param angle Rotation angle.
	*	@param flags Flags for the bitmap drawing.
	*/
	DrawRotatedImage(const Image & i, float cx, float cy, float dx, float dy, float angle, int flags);

	/** Draws a rotated Image on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:

	/** Initializes the class.
	*	@param i Image to be drawn.
	*	@param c The rotation point (relative to the image).
	*	@param d The point where bottom left corner will be drawn.
	*	@param angle Rotation angle.
	*	@param flags Flags for the bitmap drawing.
	*/
	void init(Image i, Point2D c, Point2D d, float angle, int flags);

	Point2D c,		/**< Rotation point (relative to the image).*/
			d;		/**< The point where bottom left corner will be.*/
	Image image;	/**< The Image.*/
	float angle;	/**< Rotation angle. */
	int flags;		/**< Flags for the bitmap drawing.*/
};

#endif

