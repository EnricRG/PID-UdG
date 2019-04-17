#include "DrawFilledPieslice.h"
#include "Window.h"

DrawFilledPieslice::DrawFilledPieslice(float cx, float cy, float r, Angle a, RGBColor color)
{
	init(Point2D(cx, cy), r, a, color);
}

DrawFilledPieslice::DrawFilledPieslice(Point2D c, float r, Angle a, RGBColor color)
{
	init(c, r, a, color);
}

void DrawFilledPieslice::draw(Window & w)
{
	w.filled_pieslice(pieslice.center, pieslice.r, pieslice.angle.start, pieslice.angle.delta, color);
}

void DrawFilledPieslice::init(Point2D c, float r, Angle a, RGBColor color)
{
	this->pieslice = figures::Pieslice(c, r, a);
	this->color = color;
}
