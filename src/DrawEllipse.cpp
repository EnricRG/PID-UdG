#include "DrawEllipse.h"
#include "Window.h"

DrawEllipse::DrawEllipse(float cx, float cy, float rx, float ry, PaintBrush brush)
{
	init(Point2D(cx, cy), rx, ry, brush);
}

DrawEllipse::DrawEllipse(float cx, float cy, float rx, float ry, RGBColor color, float thickness)
{
	init(Point2D(cx,cy), rx, ry, PaintBrush(color, thickness));
}

DrawEllipse::DrawEllipse(Point2D c, float rx, float ry, PaintBrush brush)
{
	init(c, rx, ry, brush);
}

DrawEllipse::DrawEllipse(Point2D c, float rx, float ry, RGBColor color, float thickness)
{
	init(c, rx, ry, PaintBrush(color, thickness));
}

void DrawEllipse::draw(Window & w)
{
	w.ellipse(ellipse.center, ellipse.rx, ellipse.ry, brush.color, brush.thickness);
}

void DrawEllipse::init(Point2D c, float rx, float ry, PaintBrush brush)
{
	ellipse = figures::Ellipse(c, rx, ry);
	this->brush = brush;
}
