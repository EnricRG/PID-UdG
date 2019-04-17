#include "DrawLine.h"
#include "Window.h"

DrawLine::DrawLine(float x1, float y1, float x2, float y2, PaintBrush brush)
{
	init(Point2D(x1, y1), Point2D(x2, y2), brush);
}

DrawLine::DrawLine(float x1, float y1, float x2, float y2, RGBColor color, float thickness)
{
	init(Point2D(x1, y1), Point2D(x2, y2), PaintBrush(color,thickness));
}

DrawLine::DrawLine(Point2D p1, Point2D p2, PaintBrush brush)
{
	init(p1, p2, brush);
}

DrawLine::DrawLine(Point2D p1, Point2D p2, RGBColor color, float thickness)
{
	init(p1, p2, PaintBrush(color, thickness));
}



void DrawLine::draw(Window & w)
{
	w.line(p1, p2, brush.color, brush.thickness);
}



void DrawLine::init(Point2D p1, Point2D p2, PaintBrush brush)
{
	this->p1 = p1; 
	this->p2 = p2; 
	this->brush = brush;
}
