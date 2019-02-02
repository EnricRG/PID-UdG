#include "DrawText.h"
#include "Window.h"

DrawText::DrawText(const Font & font, float x, float y, const std::string & text, int flags)
{
	init(font, Point2D(x, y), text, flags);
}

DrawText::DrawText(const Font & font, Point2D p, const std::string & text, int flags)
{
	init(font, p, text, flags);
}

void DrawText::draw(Window & w)
{
	w.text(font, p, text, flags);
}

void DrawText::init(const Font & font, Point2D p, const std::string & text, int flags)
{
	this->p = p;
	this->font = font;
	this->text = text;
	this->flags = flags;
}
