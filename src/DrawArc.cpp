#include "DrawArc.h"
#include "Window.h"

DrawArc::DrawArc(float cx, float cy, float r, Angle a, PaintBrush brush)
{
	init(Point2D(cx, cy), r, a, brush);
}

DrawArc::DrawArc(float cx, float cy, float r, Angle a, RGBColor color, float thickness)
{
	init(Point2D(cx, cy), r, a, PaintBrush(color, thickness));
}

DrawArc::DrawArc(Point2D c, float r, Angle a, PaintBrush brush)
{
	init(c, r, a, brush);
}

DrawArc::DrawArc(Point2D c, float r, Angle a, RGBColor color, float thickness)
{
	init(c, r, a, PaintBrush(color, thickness));
}

void DrawArc::draw(Window & w)
{
	w.arc(arc.center, arc.r, arc.angle.start, arc.angle.delta, brush.color, brush.thickness);
}

void DrawArc::init(Point2D c, float r, Angle a, PaintBrush brush)
{
	this->arc = figures::Arc(c, r, a);
	this->brush = brush;
}
