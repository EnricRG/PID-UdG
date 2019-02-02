#include "DrawFilledRectangle.h"
#include "Window.h"

DrawFilledRectangle::DrawFilledRectangle(float x1, float y1, float x2, float y2, RGBColor color)
{
	init(Point2D(x1, y1), Point2D(x2, y2), color);
}

DrawFilledRectangle::DrawFilledRectangle(Point2D p1, Point2D p2, RGBColor color)
{
	init(p1, p2, color);
}



void DrawFilledRectangle::draw(Window & w)
{
	w.filled_rectangle(rectangle.p1, rectangle.p2, color);
}



void DrawFilledRectangle::init(Point2D p1, Point2D p2, RGBColor color)
{
	rectangle = figures::Rectangle(p1, p2);
	this->color = color;
}

