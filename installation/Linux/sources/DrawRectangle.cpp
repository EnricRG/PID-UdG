#include "DrawRectangle.h"
#include "Window.h"

DrawRectangle::DrawRectangle(float x1, float y1, float x2, float y2, PaintBrush brush)
{
	init(Point2D(x1, y1), Point2D(x2, y2), brush);
}

DrawRectangle::DrawRectangle(float x1, float y1, float x2, float y2, RGBColor color, float thickness)
{
	init(Point2D(x1, y1), Point2D(x2, y2), PaintBrush(color, thickness));
}

DrawRectangle::DrawRectangle(Point2D p1, Point2D p2, PaintBrush brush)
{
	init(p1, p2, brush);
}

DrawRectangle::DrawRectangle(Point2D p1, Point2D p2, RGBColor color, float thickness)
{
	init(p1, p2, PaintBrush(color, thickness));
}



void DrawRectangle::draw(Window & w)
{
	w.rectangle(rectangle.p1, rectangle.p2, brush.color, brush.thickness);
}



void DrawRectangle::init(Point2D p1, Point2D p2, PaintBrush brush)
{
	rectangle = figures::Rectangle(p1, p2);
	this->brush = brush;
}
