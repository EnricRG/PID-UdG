#include "DrawFilledPolygonWithHoles.h"
#include "Window.h"

DrawFilledPolygonWithHoles::DrawFilledPolygonWithHoles(const float * points, const int* vertex_counts, RGBColor color)
{
	init(figures::Multipolygon(points, vertex_counts), color);
}



void DrawFilledPolygonWithHoles::draw(Window & w)
{
	w.filled_polygon_with_holes(multiPolygon.vertices, multiPolygon.vertex_counts, color);
}



void DrawFilledPolygonWithHoles::init(const figures::Multipolygon & mpg, RGBColor color)
{
	multiPolygon = mpg;
	this->color = color;
}
