#include "DrawRibbon.h"
#include "Window.h"

DrawRibbon::DrawRibbon(const float * points, int num_points, PaintBrush brush)
{
	init(figures::Ribbon(points, num_points), brush);
}

DrawRibbon::DrawRibbon(const float * points, int num_points, RGBColor color, float thickness)
{
	init(figures::Ribbon(points, num_points), PaintBrush(color, thickness));
}



void DrawRibbon::draw(Window & w)
{
	w.ribbon(ribbon.points, ribbon.num_points, brush.color, brush.thickness);
}



void DrawRibbon::init(const figures::Ribbon & r, PaintBrush brush)
{
	ribbon = r;
	this->brush = brush;
}

