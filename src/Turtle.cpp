#include "Turtle.h"
#include "Window.h"
#include "TurtleMotionFactory.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

const char* Turtle::TURTLE_CURSOR_PATH = "resources/turtle_cursor.png";
const char* Turtle::ARROW_CURSOR_PATH = "resources/arrow_cursor.png";

Turtle::Turtle(std::string name, Window * window, Point2D start_point, PaintBrush pen, Font & font, float start_direction, int turtle_motion)
{
	init(name, start_point, start_direction, pen, turtle_motion, font, window);
}

Turtle::Turtle(const Turtle & t)
{
	copy(t);
}

Turtle::~Turtle()
{
	destroy();
}

Turtle & Turtle::operator=(const Turtle & t)
{
	if (this != &t) {
		destroy();
		copy(t);
	}
	return *this;
}

std::string Turtle::getName() const
{
	return this->name;
}

float Turtle::heading() const
{
	return direction;
}

Point2D Turtle::getPos() const
{
	return currentPosition;
}

bool Turtle::isVisible() const
{
	return showPosition;
}

Point2D Turtle::forward(float dist)
{
	return move(dist, direction);
}

Point2D Turtle::back(float dist)
{
	return move(dist, direction+ALLEGRO_PI);
}

float Turtle::left(float angle)
{
	direction += angle;
	if (showPosition) {
		window->turtleMoved();
		window->cursorUpdate();
	}
	return direction;
}

float Turtle::right(float angle)
{
	direction -= angle;
	if (showPosition) {
		window->turtleMoved();
		window->cursorUpdate();
	}
	return direction;
}

Point2D Turtle::setPos(float x, float y)
{
	return setPos(Point2D(x, y));
}

Point2D Turtle::setPos(Point2D p)
{
	Point2D aux = currentPosition;
	currentPosition = p;
	if (showPosition) {
		window->turtleMoved();
		window->cursorUpdate();
	}
	return aux;
}

float Turtle::setHeading(float angle)
{
	float aux = direction;
	direction = angle;
	if (showPosition) {
		window->turtleMoved();
		window->cursorUpdate();
	}
	return aux;
}

RGBColor Turtle::setDrawingColor(RGBColor color)
{
	RGBColor aux = pen.color;
	pen.color = color;
	return aux;
}

float Turtle::setDrawingThickness(float thickness)
{
	float aux = pen.thickness;
	pen.thickness = thickness;
	return aux;
}

PaintBrush Turtle::setPen(PaintBrush pen)
{
	PaintBrush aux = this->pen;
	this->pen = pen;
	return aux;
}

void Turtle::show()
{
	showPosition = true;
	window->turtleMoved();
}

void Turtle::hide()
{
	showPosition = false;
	window->turtleMoved();
}

void Turtle::penUp()
{
	painting = false;
}

void Turtle::penDown()
{
	painting = true;
}

void Turtle::swapPen()
{
	painting = !painting;
}

void Turtle::label(std::string text, int flags)
{
	window->text(font, currentPosition, text, flags);
}

void Turtle::label(Font f, std::string text, int flags)
{
	window->text(f, currentPosition, text, flags);
}

void Turtle::image(Image i, int flags)
{
	window->image(i, currentPosition, flags);
}

void Turtle::image(std::string image_path, int flags)
{
	window->image(image_path, currentPosition, flags);
}

void Turtle::changeMotion(int turtle_motion)
{
	delete turtleMotion;
	turtleMotion = TurtleMotionFactory::makeTurtleMotion(turtle_motion);
}

void Turtle::setFont(Font f)
{
	font = f;
}

void Turtle::changeCursorColor(RGBColor color)
{
	cursor = Image(createArrowCursor(color));
	window->cursorUpdate();
}

void Turtle::drawCursor()
{
	Point2D rotation_point = Point2D(cursor.width() / 2, cursor.height() / 2);
	Point2D positioning = Point2D(1, 0);
	window->turtle_rotated_image(cursor, rotation_point, currentPosition + positioning, direction);
}

void Turtle::init(std::string name, Point2D position, float direction, PaintBrush pen, int turtle_motion, Font & font, Window * window)
{
	this->name = name;
	this->currentPosition = position;
	this->direction = direction;
	this->turtleMotion = TurtleMotionFactory::makeTurtleMotion(turtle_motion);
	this->window = window;
	this->pen = pen;
	this->font = font;
	painting = true;
	showPosition = false;
	cursor = Image(initCursor(ARROW_CURSOR_PATH, BLACK));
}

ALLEGRO_BITMAP* Turtle::initCursor(const char * cursor_path, RGBColor color)
{
	if (!al_init()) throw AllegroException("could not initialize Allegro system");

	if(!al_init_image_addon()) throw AllegroException("could not initialize Allegro image system");
	
	return createArrowCursor(color);

	//return al_load_bitmap(cursor_path);
}

void Turtle::copy(const Turtle & t)
{
	name = t.name;
	currentPosition = t.currentPosition;
	direction = t.direction;
	pen = t.pen;
	painting = t.painting;
	showPosition = t.showPosition;
	turtleMotion = TurtleMotionFactory::makeTurtleMotion(t.turtleMotion->type());
	window = t.window;
	font = t.font;
	cursor = t.cursor;
}

void Turtle::destroy() {
	delete turtleMotion;
	window = NULL;
}

Point2D Turtle::move(float dist, float direction)
{
	Point2D next_pos = turtleMotion->nextPosition(currentPosition, direction, dist, window->getWindowSpec());
	Point2D current_pos = currentPosition;
	currentPosition = next_pos;

	if (painting) window->turtleLine(current_pos, next_pos, pen.color, pen.thickness, showPosition);

	if (showPosition) {
		window->turtleMoved();
		window->cursorUpdate();
	}

	return next_pos;
}

ALLEGRO_BITMAP * Turtle::createArrowCursor(RGBColor color)
{
	ALLEGRO_BITMAP *cursor = al_create_bitmap(32, 32), *aux = al_create_bitmap(10,10), *previous;
	ALLEGRO_COLOR allegro_color = color.toAllegroColor();

	previous = al_get_target_bitmap();
	al_set_target_bitmap(aux);

	al_draw_filled_rectangle(0, 0, 2, 2, allegro_color);
	al_draw_filled_rectangle(1, 1, 4, 3, allegro_color);
	al_draw_filled_rectangle(2, 2, 6, 4, allegro_color);
	al_draw_filled_rectangle(3, 3, 8, 6, allegro_color);
	al_draw_pixel(9, 5, allegro_color);
	al_draw_filled_rectangle(2, 5, 6, 7, allegro_color);
	al_draw_filled_rectangle(1, 6, 4, 8, allegro_color);
	al_draw_filled_rectangle(0, 7, 2, 9, allegro_color);
	
	al_set_target_bitmap(cursor);
	al_draw_bitmap(aux, 12, 11, 0);

	al_set_target_bitmap(previous);
	return cursor;
}
