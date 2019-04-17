#include "DrawFilledCircle.h"
#include "Window.h"

DrawFilledCircle::DrawFilledCircle(float cx, float cy, float r, RGBColor color)
{
	init(Point2D(cx, cy), r, color);
}

DrawFilledCircle::DrawFilledCircle(Point2D c, float r, RGBColor color)
{
	init(c, r, color);
}

void DrawFilledCircle::draw(Window & w)
{
	w.filled_circle(circle.center, circle.r, color);
}

void DrawFilledCircle::init(Point2D c, float r, RGBColor color)
{
	this->circle = figures::Circle(c, r);
	this->color = color;
}
