#include "DrawPixel.h"
#include "Window.h"



DrawPixel::DrawPixel(float x, float y, RGBColor color)
{
	init(Point2D(x, y), color);
}

DrawPixel::DrawPixel(Point2D p, RGBColor color)
{
	init(p, color);
}

void DrawPixel::draw(Window & w)
{
	w.pixel(p, color);
}

void DrawPixel::init(Point2D p, RGBColor color)
{
	this->p = p;
	this->color = color;
}
