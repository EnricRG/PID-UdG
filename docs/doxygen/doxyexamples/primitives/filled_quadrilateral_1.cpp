#include "WindowAddon.h"

int main(int argc, char **argv) {
	Window w(201, 201); //White background color and black drawing color by default

	w.filled_quadrilateral(50, 50, 100, 55, 120, 150, 40, 110, BLACK); //thickness 1.0 by default

	w.waitWindowCloseButton();

	return 0;
}