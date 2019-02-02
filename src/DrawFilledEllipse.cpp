#include "DrawFilledEllipse.h"
#include "Window.h"

DrawFilledEllipse::DrawFilledEllipse(float cx, float cy, float rx, float ry, RGBColor color)
{
	init(Point2D(cx, cy), rx, ry, color);
}

DrawFilledEllipse::DrawFilledEllipse(Point2D c, float rx, float ry, RGBColor color)
{
	init(c, rx, ry, color);
}

void DrawFilledEllipse::draw(Window & w)
{
	w.filled_ellipse(ellipse.center, ellipse.rx, ellipse.ry, color);
}

void DrawFilledEllipse::init(Point2D c, float rx, float ry, RGBColor color)
{
	ellipse = figures::Ellipse(c, rx, ry);
	this->color = color;
}
