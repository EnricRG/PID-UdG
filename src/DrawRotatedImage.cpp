#include "DrawRotatedImage.h"
#include "Window.h"

DrawRotatedImage::DrawRotatedImage(const Image & i, Point2D c, Point2D d, float angle, int flags)
{
	init(i, c, d, angle, flags);
}

DrawRotatedImage::DrawRotatedImage(const Image & i, float cx, float cy, float dx, float dy, float angle, int flags)
{
	init(i, Point2D(cx, cy), Point2D(dx, dy), angle, flags);
}

void DrawRotatedImage::draw(Window & w)
{
	w.rotated_image(image, c, d, angle, flags);
}

void DrawRotatedImage::init(Image i, Point2D c, Point2D d, float angle, int flags)
{
	image = i;
	this->c = c;
	this->d = d;
	this->angle = angle;
	this->flags = flags;
}
