#include "DrawFilledTriangle.h"
#include "Window.h"

DrawFilledTriangle::DrawFilledTriangle(float x1, float y1, float x2, float y2, float x3, float y3, RGBColor color)
{
	init(Point2D(x1, y1), Point2D(x2, y2), Point2D(x3, y3), color);
}

DrawFilledTriangle::DrawFilledTriangle(Point2D p1, Point2D p2, Point2D p3, RGBColor color)
{
	init(p1, p2, p3, color);
}



void DrawFilledTriangle::draw(Window & w)
{
	w.filled_triangle(triangle.p1, triangle.p2, triangle.p3, color);
}



void DrawFilledTriangle::init(Point2D p1, Point2D p2, Point2D p3, RGBColor color)
{
	triangle = figures::Triangle(p1, p2, p3);
	this->color = color;
}
