#include "DrawTurtleLine.h"
#include "Window.h"

DrawTurtleLine::DrawTurtleLine(float x1, float y1, float x2, float y2, PaintBrush brush, bool showing_cursor)
{
	init(Point2D(x1, y1), Point2D(x2, y2), brush, showing_cursor);
}

DrawTurtleLine::DrawTurtleLine(float x1, float y1, float x2, float y2, RGBColor color, float thickness, bool showing_cursor)
{
	init(Point2D(x1, y1), Point2D(x2, y2), PaintBrush(color, thickness), showing_cursor);
}

DrawTurtleLine::DrawTurtleLine(Point2D p1, Point2D p2, PaintBrush brush, bool showing_cursor)
{
	init(p1, p2, brush, showing_cursor);
}

DrawTurtleLine::DrawTurtleLine(Point2D p1, Point2D p2, RGBColor color, float thickness, bool showing_cursor)
{
	init(p1, p2, PaintBrush(color, thickness), showing_cursor);
}



void DrawTurtleLine::draw(Window & w)
{
	if (showing_cursor) w.turtleMoved();
	w.turtleLine(p1, p2, brush.color, brush.thickness, showing_cursor);
}



void DrawTurtleLine::init(Point2D p1, Point2D p2, PaintBrush brush, bool showing_cursor)
{
	this->p1 = p1;
	this->p2 = p2;
	this->brush = brush;
	this->showing_cursor = showing_cursor;
}