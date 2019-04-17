#include "DrawPolygon.h"
#include "Window.h"

DrawPolygon::DrawPolygon(const float * points, int num_points, PaintBrush brush)
{
	init(figures::Polygon(points, num_points), brush);
}

DrawPolygon::DrawPolygon(const float * points, int num_points, RGBColor color, float thickness)
{
	init(figures::Polygon(points, num_points), PaintBrush(color, thickness));
}



void DrawPolygon::draw(Window & w)
{
	w.polygon(polygon.points, polygon.num_points, brush.color, brush.thickness);
}



void DrawPolygon::init(const figures::Polygon & pg, PaintBrush brush)
{
	polygon = pg;
	this->brush = brush;
}

