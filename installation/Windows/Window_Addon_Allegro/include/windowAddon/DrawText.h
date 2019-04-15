#ifndef DRAWTEXT_H
#define DRAWTEXT_H

#include <string>

#include "Drawable.h"
#include "Point2D.h"
#include "Font.h"

/** @brief Implementation of Drawable interface.
*	This class is capable of storing the information needed to draw text on a Window.
*/
#ifdef _WIN32
	class DLL_EXPORT DrawText : public Drawable
#else
	class DrawText : public Drawable
#endif
{
public:

	/** Destructor of the class
	*/
	~DrawText() {};

	/** One of the parametric constructors of the class.
	*	@param font The font used to write the text.
	*	@param x X coordinate where the text will be drawn
	*	@param y Y coordinate where the text will be drawn.
	*	@param text The text that will be written.
	*	@param flags This parameter can be used to specify the alignment of the text. See @ref text_align for more details.
	*/
	DrawText(const Font & font, float x, float y, const std::string & text, int flags);
	
	/** One of the parametric constructors of the class.
	*	@param font The font used to write the text.
	*	@param p coordinates where the text will be drawn.
	*	@param text The text that will be written.
	*	@param flags This parameter can be used to specify the alignment of the text. See @ref text_align for more details.
	*/
	DrawText(const Font & font, Point2D p, const std::string & text, int flags);

	/** Draws a rotated Image on the Window @p w.
	*	@param w Target Window to draw.
	*/
	void draw(Window & w);

protected:

	/** Initializes the class.
	*	@param font The font used to write the text.
	*	@param p coordinates where the text will be drawn.
	*	@param text The text that will be written.
	*	@param flags This parameter can be used to specify the alignment of the text.
	*/
	void init(const Font & font, Point2D p, const std::string & text, int flags);

	Point2D p;			/**< Center of the text box.*/
	Font font;			/**< Font used to draw the text.*/
	std::string text;	/**< Text.*/
	int flags;			/**< Specifies the alignment of the text.*/
};

#endif
