#include "DrawFilledRoundedRectangle.h"
#include "Window.h"

DrawFilledRoundedRectangle::DrawFilledRoundedRectangle(float x1, float y1, float x2, float y2, float rx, float ry, RGBColor color)
{
	init(Point2D(x1, y1), Point2D(x2, y2), rx, ry, color);
}

DrawFilledRoundedRectangle::DrawFilledRoundedRectangle(Point2D p1, Point2D p2, float rx, float ry, RGBColor color)
{
	init(p1, p2, rx, ry, color);
}



void DrawFilledRoundedRectangle::draw(Window & w)
{
	w.filled_rounded_rectangle(rectangle.p1, rectangle.p2, rx, ry, color);
}



void DrawFilledRoundedRectangle::init(Point2D p1, Point2D p2, float rx, float ry, RGBColor color)
{
	rectangle = figures::Rectangle(p1, p2);
	this->rx = rx;
	this->ry = ry;
	this->color = color;
}
