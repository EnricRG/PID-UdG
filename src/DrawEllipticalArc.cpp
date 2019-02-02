#include "DrawEllipticalArc.h"
#include "Window.h"

DrawEllipticalArc::DrawEllipticalArc(float cx, float cy, float rx, float ry, Angle a, PaintBrush brush)
{
	init(Point2D(cx, cy), rx, ry, a, brush);
}

DrawEllipticalArc::DrawEllipticalArc(float cx, float cy, float rx, float ry, Angle a, RGBColor color, float thickness)
{
	init(Point2D(cx, cy), rx, ry, a, PaintBrush(color, thickness));
}

DrawEllipticalArc::DrawEllipticalArc(Point2D c, float rx, float ry, Angle a, PaintBrush brush)
{
	init(c, rx, ry, a, brush);
}

DrawEllipticalArc::DrawEllipticalArc(Point2D c, float rx, float ry, Angle a, RGBColor color, float thickness)
{
	init(c, rx, ry, a, PaintBrush(color, thickness));
}

void DrawEllipticalArc::draw(Window & w)
{
	w.elliptical_arc(arc.center, arc.rx, arc.ry, arc.angle.start, arc.angle.delta, brush.color, brush.thickness);
}

void DrawEllipticalArc::init(Point2D c, float rx, float ry, Angle a, PaintBrush brush)
{
	this->arc = figures::EllipticalArc(c, rx, ry, a);
	this->brush = brush;
}
