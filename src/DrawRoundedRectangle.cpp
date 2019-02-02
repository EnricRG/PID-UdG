#include "DrawRoundedRectangle.h"
#include "Window.h"

DrawRoundedRectangle::DrawRoundedRectangle(float x1, float y1, float x2, float y2, float rx, float ry, PaintBrush brush)
{
	init(Point2D(x1, y1), Point2D(x2, y2), rx, ry, brush);
}

DrawRoundedRectangle::DrawRoundedRectangle(float x1, float y1, float x2, float y2, float rx, float ry, RGBColor color, float thickness)
{
	init(Point2D(x1, y1), Point2D(x2, y2), rx, ry, PaintBrush(color, thickness));
}

DrawRoundedRectangle::DrawRoundedRectangle(Point2D p1, Point2D p2, float rx, float ry, PaintBrush brush)
{
	init(p1, p2, rx, ry, brush);
}

DrawRoundedRectangle::DrawRoundedRectangle(Point2D p1, Point2D p2, float rx, float ry, RGBColor color, float thickness)
{
	init(p1, p2, rx, ry, PaintBrush(color, thickness));
}



void DrawRoundedRectangle::draw(Window & w)
{
	w.rounded_rectangle(rectangle.p1, rectangle.p2, rx, ry, brush.color, brush.thickness);
}



void DrawRoundedRectangle::init(Point2D p1, Point2D p2, float rx, float ry, PaintBrush brush)
{
	rectangle = figures::Rectangle(p1, p2);
	this->rx = rx;
	this->ry = ry;
	this->brush = brush;
}
