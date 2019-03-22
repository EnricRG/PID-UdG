#ifndef TURTLE_H
#define TURTLE_H

#include "Point2D.h"
#include "PaintBrush.h"
#include "TurtleMotion.h"
#include "Font.h"
#include "Exceptions.h"
#include "Image.h"

#include <string>

class Window;
//struct Image;

class Turtle
{
public:

	Turtle(std::string name, Window * window, Point2D start_point, PaintBrush pen, Font & font, float start_direction = 0, int turtle_motion = WINDOW_MODE);
	Turtle(const Turtle &t);
	~Turtle();

	Turtle& operator=(const Turtle &t);

	std::string getName() const;
	double heading() const;
	Point2D getPos() const;
	bool isVisible() const;

	Point2D forward(double dist);
	Point2D back(double dist);
	double left(double angle);
	double right(double angle);
	Point2D setPos(float x, float y);
	Point2D setPos(Point2D p);
	double setHeading(double angle);
	RGBColor setDrawingColor(RGBColor color);
	float setDrawingThickness(float thickness);
	PaintBrush setPen(PaintBrush pen);
	void show();
	void hide();
	void penUp();
	void penDown();
	void swapPen();
	void label(std::string text, int flags);
	void label(Font f, std::string text, int flags);
	void image(Image i, int flags = 0);
	void image(std::string image_path, int flags = 0);

	void changeMotion(int turtle_motion);
	void setFont(Font f);

	void changeCursorColor(RGBColor color);
	void drawCursor();
	
private:
	static const char * TURTLE_CURSOR_PATH;
	static const char * ARROW_CURSOR_PATH;

	void init(std::string name, Point2D position, double direction, PaintBrush pen, int turtle_motion, Font & font, Window * window);
	static ALLEGRO_BITMAP* initCursor(const char * cursor_path, RGBColor color);
	void copy(const Turtle & t);
	void destroy();
	Point2D move(double dist, double direction);
	void teleport(Point2D pos);
	static ALLEGRO_BITMAP* createArrowCursor(RGBColor color);

	std::string name;
	Point2D currentPosition;
	double direction;
	PaintBrush pen;
	bool painting;
	bool showPosition;
	TurtleMotion* turtleMotion;
	Font font;
	Image cursor;

	Window* window;
};

#endif