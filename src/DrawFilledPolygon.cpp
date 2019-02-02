#include "DrawFilledPolygon.h"
#include "Window.h"

DrawFilledPolygon::DrawFilledPolygon(const float * points, int num_points, RGBColor color)
{
	init(figures::Polygon(points, num_points), color);
}



void DrawFilledPolygon::draw(Window & w)
{
	w.filled_polygon(polygon.points, polygon.num_points, color);
}



void DrawFilledPolygon::init(const figures::Polygon & pg, RGBColor color)
{
	polygon = pg;
	this->color = color;
}
