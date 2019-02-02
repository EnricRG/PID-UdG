#include "DrawCircle.h"
#include "Window.h"

DrawCircle::DrawCircle(float cx, float cy, float r, PaintBrush brush)
{
	init(Point2D(cx, cy), r, brush);
}

DrawCircle::DrawCircle(float cx, float cy, float r, RGBColor color, float thickness)
{
	init(Point2D(cx, cy), r, PaintBrush(color, thickness));
}

DrawCircle::DrawCircle(Point2D c, float r, PaintBrush brush)
{
	init(c, r, brush);
}

DrawCircle::DrawCircle(Point2D c, float r, RGBColor color, float thickness)
{
	init(c, r, PaintBrush(color, thickness));
}

void DrawCircle::draw(Window & w)
{
	w.circle(circle.center, circle.r, brush.color, brush.thickness);
}

void DrawCircle::init(Point2D c, float r, PaintBrush brush)
{
	this->circle = figures::Circle(c, r);
	this->brush = brush;
}
