#include "Window.h"
#include <iostream>
#include "DrawLine.h"
#include "Font.h"
#include "Image.h"
#include "Event.h"

#include <list>

const double PI = ALLEGRO_PI;

void wait(Window & w) {
	//w.waitWindowCloseButton();
	//w.waitMouseLeftClick(true);
	//w.waitMouseRightClick(true);
	//w.waitMouseAnyClick(true);
	//w.waitAnyKeypress(true);
	w.waitKeypress(ALLEGRO_KEY_SPACE, true);
}

void primitives(Window & w, Image & i) {

	w.useRadians();

	std::string text = "Projecte d'Innovacio Docent\nImplementacio d'una classe Window en C++\ncom a interficie d'alt nivell a Allegro";
	Point2D textPos(500, 300);
	Font f("Fonts\\open-sans\\OpenSans-Light.ttf", BLUE, 14, 0);
	w.addFont("OpenSansBold", "Fonts\\open-sans\\OpenSans-Bold.ttf", LIME, 16);

	w.text(500, 300, text.c_str(), TEXT_ALIGN_CENTER);
	w.text(f, 500, 500, text.c_str(), TEXT_ALIGN_LEFT);
	w.text("OpenSansBold", 500, 100, text.c_str(), TEXT_ALIGN_RIGHT);
	w.pixel(500, 300, RED); //center of the text

	w.line(Point2D(110, 5), Point2D(110, 600), RED);
	w.triangle(Point2D(0, 0), Point2D(48, 0), Point2D(0, 48), RED);
	w.filled_triangle(Point2D(52, 0), Point2D(100, 0), Point2D(100, 48), RED);
	w.rectangle(Point2D(0, 50), Point2D(100, 100), RED);
	w.filled_rectangle(Point2D(0, 102), Point2D(100, 152), RED);
	w.filled_rounded_rectangle(Point2D(0, 256), Point2D(100, 206), 5, 5, RED);
	w.rounded_rectangle(Point2D(0, 204), Point2D(100, 154), 5, 5, RED);
	w.ellipse(Point2D(20, 280), 20, 15, RED);
	w.filled_ellipse(Point2D(62, 280), 20, 15, RED);
	w.circle(Point2D(20, 322), 20, RED);
	w.filled_circle(Point2D(62, 322), 20, RED);
	w.arc(Point2D(20, 364), 20, 0, PI, RED);
	w.elliptical_arc(Point2D(62, 364), 20, 15, 0, PI, RED);
	w.pieslice(Point2D(20, 390), 20, 0, PI/2, RED);
	w.filled_pieslice(Point2D(42, 390), 20, 0, PI/2, RED);
	
	Point2D spline_points[4];
	spline_points[0] = Point2D(25, 400 + 20);
	spline_points[1] = Point2D(40, 430 + 20);
	spline_points[2] = Point2D(35, 445 + 20);
	spline_points[3] = Point2D(20, 450 + 20);
	w.spline(spline_points, RED);
	
	Point2D ribbon_points[4];
	ribbon_points[0] = Point2D(25 + 40, 400 + 20);
	ribbon_points[1] = Point2D(40 + 40, 430 + 20);
	ribbon_points[2] = Point2D(35 + 40, 445 + 20);
	ribbon_points[3] = Point2D(20 + 40, 450 + 20);
	w.ribbon(ribbon_points, 4, RED);

	Point2D polyline_points[4];
	polyline_points[0] = Point2D(20, 455 + 20);
	polyline_points[1] = Point2D(30, 455 + 20);
	polyline_points[2] = Point2D(40, 455 + 40 + 20);
	polyline_points[3] = Point2D(10, 455 + 40 + 20);
	w.polyline(polyline_points, 4, RED);

	Point2D polygon_points[4];
	polygon_points[0] = Point2D(20 + 50, 455 + 20);
	polygon_points[1] = Point2D(30 + 50, 455 + 20);
	polygon_points[2] = Point2D(40 + 50, 455 + 40 + 20);
	polygon_points[3] = Point2D(10 + 50, 455 + 40 + 20);
	w.polygon(polygon_points, 4, RED);

	Point2D filled_polygon_points[4];
	filled_polygon_points[0] = Point2D(20, 500 + 20);
	filled_polygon_points[1] = Point2D(30, 500 + 20);
	filled_polygon_points[2] = Point2D(40, 500 + 40 + 20);
	filled_polygon_points[3] = Point2D(10, 500 + 40 + 20);
	w.filled_polygon(filled_polygon_points, 4, RED);

	Point2D filled_polygon_with_holes[8]; //the following initialization order is mandatory in order to get this primitve working
	filled_polygon_with_holes[0] = Point2D(20 + 50, 500 + 20); //bottom left corner
	filled_polygon_with_holes[1] = Point2D(30 + 50, 500 + 20); //bottom right corner
	filled_polygon_with_holes[2] = Point2D(40 + 50, 500 + 40 + 20); //top right corner
	filled_polygon_with_holes[3] = Point2D(10 + 50, 500 + 40 + 20); //top left corner
	filled_polygon_with_holes[4] = Point2D(20 + 50 + 4, 500 + 4 + 20); //bottom left hole corner
	filled_polygon_with_holes[5] = Point2D(10 + 50 + 4, 500 + 40 - 4 + 20); //top left hole corner
	filled_polygon_with_holes[6] = Point2D(40 + 50 - 4, 500 + 40 - 4 + 20); //top right hole corner
	filled_polygon_with_holes[7] = Point2D(30 + 50 - 4 , 500 + 4 + 20); //bottom right hole corner
	
	int vertex_counts[] = { 4,4,0 };
	w.filled_polygon_with_holes(filled_polygon_with_holes, vertex_counts, RED);

	//saveToFile is not a primitive
	w.saveToFile("primitives", "jpg");
	w.saveToFile("primitives");
	w.image(i, Point2D(700, 300));
	w.image("C:\\Users\\Enric-LAPTOP\\Downloads\\city_icon.png", Point2D(700, 50)); // double \\ to escape special ASCI characters

	w.rotated_image(i, Point2D(0,0), Point2D(1000, 300), PI/2);

	wait(w);

	w.changeBackgroundColor(LIGHTGRAY);

	wait(w);

	w.changeBackgroundColor(WHITE);

	w.useDegrees();
}

void simpleLines(Window & w) {
	//CIAN LINE
	w.line(Point2D(50, 50), Point2D(150, 50), CIAN, 3);
	w.line(Point2D(150, 50), Point2D(300, 300), CIAN, 3);
	w.line(Point2D(300, 300), Point2D(450, 300), CIAN, 3);

	//DRAWING COLOR LINE
	w.line(Point2D(50, 50 + 30), Point2D(150, 50 + 30));
	w.line(Point2D(150, 50 + 30), Point2D(300, 300 + 30));
	w.line(Point2D(300, 300 + 30), Point2D(450, 300 + 30));

	//w.rest(10);
	wait(w);

	w.changeBackgroundColor(BLACK);

	//w.rest(10);
	wait(w);

	w.disableLogging();

	w.changeBackgroundColor(WHITE);

	w.enableLogging();
	//w.rest(3);
}

void draw(Window & w) {

	Drawable* some[3];
	some[0] = new DrawLine(Point2D(50, 50), Point2D(150, 50), CIAN, 3);
	some[1] = new DrawLine(Point2D(150, 50), Point2D(300, 300), LIME, 3);
	some[2] = new DrawLine(Point2D(300, 300), Point2D(450, 300), BLUE, 3);
	
	w.draw(some, 3);

	std::list<Drawable*> list;
	list.push_back(some[0]);
	list.push_back(some[1]);
	list.push_back(some[2]);
	w.draw(list.begin(), list.end());

	for (int i = 0; i < 3; i++) { delete some[i]; }
}

void turtleDemo(Window & w) {
	w.t_show();

	w.t_setPos(Point2D(100, 100));

	wait(w);

	w.t_forward(100);
	w.t_left(45);

	//w.rest(0.5);
	wait(w);

	w.t_forward(300);
	w.t_right(45);
	
	//w.rest(0.5);
	wait(w);

	w.t_back(200);

	//w.rest(0.5);
	wait(w);

	std::string new_turtle_name = "Raphael";
	w.addTurtle(new_turtle_name);
	w.t_show("Raphael");

	//w.setActiveTurtle("Raphael");

	w.t_setPos(new_turtle_name, Point2D(500, 300));

	wait(w);

	w.t_forward(new_turtle_name, 100);
	w.t_left(new_turtle_name, 45);

	//w.rest(0.5);
	wait(w);

	w.t_forward(new_turtle_name, 300);
	w.t_right(new_turtle_name, 45);

	//w.rest(0.5);
	wait(w);

	w.t_forward(new_turtle_name, 200);

	//w.rest(0.5);
	wait(w);

	w.changeBackgroundColor(LIGHTGRAY);

	wait(w);

	w.changeBackgroundColor(WHITE);

	w.useDegrees();
}

void eventHandling(Window & w) {
	WindowEvent ev;

	do {
		ev = w.waitWindowEvent();
		switch (ev.type) {
			case WINDOW_EVENT_DISPLAY_SWITCH_IN:
				w.update();
				std::cout << "Update" << std::endl;
				break;
		}
	} while (ev.type != WINDOW_EVENT_DISPLAY_CLOSE);
}

int main3(int argc, char **argv)
{
	Image i("C:\\Users\\Enric-LAPTOP\\Downloads\\city_icon.png");
	int width = 1280, height = 680;
	Window w("Projecte d'Innovacio Docent", width, height, WHITE, RED); //4th parameter is the drawing color
	Window w2;

	//w.setAutoUpdate(true);
	w.enableLogging();
	/*
	Font f("Fonts/open-sans/OpenSans-Bold.ttf", BLACK, 32, 0);
	Point2D warningTextPos(width / 2, height / 2);
	
	w.text(f, warningTextPos, "Simple Lines demo:\n\nDrawing raw and with class parameters\nAnd redrawing from log", TEXT_ALIGN_CENTER);
	//w.rest(7);
	wait(w);
	w.clear();

	w2.clear();
	w2.rest(0.5);
	w2.line(0, 0, 300, 300, RED);
	simpleLines(w);

	w.clear();
	w.text(f, warningTextPos, "Primitives demo:\n\nShowing all primitives", TEXT_ALIGN_CENTER);
	//w.rest(7);
	wait(w);
	w.clear(); 

	w2.clear();
	w2.rest(0.5);
	w2.line(0, 0, 300, 300, RED);
	primitives(w,i);
	//w.rest(20);
	wait(w);

	w.clear();
	w.text(f, warningTextPos, "Drawable interface demo:\n\nDrawing from an array of Drawable objects", TEXT_ALIGN_CENTER);
	//w.rest(7);
	wait(w);
	w.clear();

	w2.clear();
	w2.rest(0.5);
	w2.line(0, 0, 300, 300, RED);
	draw(w);
	//w.rest(10);
	wait(w);

	w.clear();
	w.text(f, warningTextPos, "Turtle demo:\n\nA little demo of Turtle motion", TEXT_ALIGN_CENTER);
	//w.rest(7);
	wait(w);
	w.clear();
	*/
	w2.clear();
	w2.rest(0.5);
	w2.line(0, 0, 300, 300, RED);
	turtleDemo(w);
	//w.rest(5);
	//wait(w);

	//w.clear();
	w2.clear();
	w2.rest(0.5);
	w2.line(0, 0, 300, 300, RED);
 	eventHandling(w);

	//w.waitWindowCloseButton();
	//w.waitMouseAnyClick(true);
	//w.waitAnyKeypress(true);
	//w.waitKeypress(ALLEGRO_KEY_SPACE, true);
	
	return 0;
}

#include <cmath>
#include "CommonUtils.h"

int main(int argc, char **argv) {
	
	Window w(500,500);

	w.t_show();

	w.t_changeMotion(WRAP_MODE);

	w.t_setPos(600,350);

	w.t_left(180);
	w.t_forward(1100);

	w.waitWindowCloseButton();
	

	//std::cout << atan2(-5,-5)*180/PI << std::endl;
	return 0;
}