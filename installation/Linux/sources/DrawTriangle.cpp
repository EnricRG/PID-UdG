#include "DrawTriangle.h"
#include "Window.h"

DrawTriangle::DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, PaintBrush brush)
{
	init(Point2D(x1, y1), Point2D(x2, y2), Point2D(x3,y3), brush);
}

DrawTriangle::DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, RGBColor color, float thickness)
{
	init(Point2D(x1, y1), Point2D(x2, y2), Point2D(x3, y3), PaintBrush(color, thickness));
}

DrawTriangle::DrawTriangle(Point2D p1, Point2D p2, Point2D p3, PaintBrush brush)
{
	init(p1, p2, p3, brush);
}

DrawTriangle::DrawTriangle(Point2D p1, Point2D p2, Point2D p3, RGBColor color, float thickness)
{
	init(p1, p2, p3, PaintBrush(color, thickness));
}



void DrawTriangle::draw(Window & w)
{
	w.triangle(triangle.p1, triangle.p2, triangle.p3, brush.color, brush.thickness);
}



void DrawTriangle::init(Point2D p1, Point2D p2, Point2D p3, PaintBrush brush)
{
	triangle = figures::Triangle(p1, p2, p3);
	this->brush = brush;
}

