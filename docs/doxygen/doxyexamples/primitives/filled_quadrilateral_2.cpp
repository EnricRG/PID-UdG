#include "WindowAddon.h"

int main(int argc, char **argv) {
	Window w(201, 201); //White background color and black drawing color by default

	Point2D p1(50, 50);
	Point2D p2(100, 55);
	Point2D p3(120, 150);
	Point2D p4(40, 110);
	w.filled_quadrilateral(p1, p2, p3, p4, BLACK); 

	w.waitWindowCloseButton();

	return 0;
}