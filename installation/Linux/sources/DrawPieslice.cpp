#include "DrawPieslice.h"
#include "Window.h"

DrawPieslice::DrawPieslice(float cx, float cy, float r, Angle a, PaintBrush brush)
{
	init(Point2D(cx, cy), r, a, brush);
}

DrawPieslice::DrawPieslice(float cx, float cy, float r, Angle a, RGBColor color, float thickness)
{
	init(Point2D(cx, cy), r, a, PaintBrush(color, thickness));
}

DrawPieslice::DrawPieslice(Point2D c, float r, Angle a, PaintBrush brush)
{
	init(c, r, a, brush);
}

DrawPieslice::DrawPieslice(Point2D c, float r, Angle a, RGBColor color, float thickness)
{
	init(c, r, a, PaintBrush(color, thickness));
}

void DrawPieslice::draw(Window & w)
{
	w.pieslice(pieslice.center, pieslice.r, pieslice.angle.start, pieslice.angle.delta, brush.color, brush.thickness);
}

void DrawPieslice::init(Point2D c, float r, Angle a, PaintBrush brush)
{
	this->pieslice = figures::Pieslice(c, r, a);
	this->brush = brush;
}
