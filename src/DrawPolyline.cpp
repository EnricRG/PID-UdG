#include "DrawPolyline.h"
#include "Window.h"

DrawPolyline::DrawPolyline(const float * points, int num_points, PaintBrush brush)
{
	init(figures::Polyline(points, num_points), brush);
}

DrawPolyline::DrawPolyline(const float * points, int num_points, RGBColor color, float thickness)
{
	init(figures::Polyline(points, num_points), PaintBrush(color, thickness));
}



void DrawPolyline::draw(Window & w)
{
	w.polyline(polyline.points, polyline.num_points, brush.color, brush.thickness);
}



void DrawPolyline::init(const figures::Polyline & pl, PaintBrush brush)
{
	polyline = pl;
	this->brush = brush;
}

