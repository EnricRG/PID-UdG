#include "DrawSpline.h"
#include "Window.h"

DrawSpline::DrawSpline(float * points, PaintBrush brush)
{
	init(figures::Spline(points), brush);
}

DrawSpline::DrawSpline(float * points, RGBColor color, float thickness)
{
	init(figures::Spline(points), PaintBrush(color, thickness));
}



void DrawSpline::draw(Window & w)
{
	w.spline(spline.points, brush.color, brush.thickness);
}



void DrawSpline::init(const figures::Spline & s, PaintBrush brush)
{
	spline = s;
	this->brush = brush;
}
