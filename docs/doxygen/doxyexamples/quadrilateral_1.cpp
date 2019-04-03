#include "WindowAddon.h"

int main(int argc, char **argv) {
	Window w(201, 201); //White background color and black drawing color by default

	w.quadrilateral(50, 50, 40, 110, 120, 150, 100, 55, BLACK); //thickness 1.0 by default

	w.waitWindowCloseButton();

	return 0;
}