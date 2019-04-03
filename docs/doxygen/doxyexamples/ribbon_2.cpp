#include "Window.h"

int main(int argc, char **argv) {
	Window w(201, 201);

	Point2D points[4];
	points[0] = Point2D(100, 100);
	points[1] = Point2D(115, 130);
	points[2] = Point2D(110, 145);
	points[3] = Point2D(95, 150);
	
	w.ribbon(points, 4, BLACK); //thickness 1.0 by default

	w.waitWindowCloseButton();
	
	return 0;
}