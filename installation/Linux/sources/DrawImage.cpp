#include "DrawImage.h"
#include "Window.h"

DrawImage::DrawImage(const Image & i, Point2D p, int flags)
{
	init(i, p, flags);
}

DrawImage::DrawImage(const Image & i, float x, float y, int flags)
{
	init(i, Point2D(x, y), flags);
}

void DrawImage::draw(Window & w)
{
	w.image(image, p, flags);
}

void DrawImage::init(Image i, Point2D p, int flags)
{
	this->image = i;
	this->p = p;
	this->flags = flags;
}