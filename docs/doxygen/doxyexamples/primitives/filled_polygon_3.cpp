#include "WindowAddon.h"

int main(int argc, char **argv) {
	Window w(201, 201);

	float points[8] = {
		90, 80,
		110, 80,
		120, 130,
		80, 130
	};

	w.polygon(points, 4); //Using w drawing parameters (in this case, black drawing color)

	w.waitWindowCloseButton();
	
	return 0;
}