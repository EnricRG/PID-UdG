#include "WindowAddon.h"

int main(int argc, char **argv) {
	Window w(201, 201);

	float points[8] = {
		90, 80,
		110, 80,
		120, 130,
		80, 130
	};

	w.polyline(points, 4, LINE_CAP_NONE, LINE_CAP_NONE); //miter_limit is 0 by default. Using w drawing parameters (in this case, black drawing color and thickness 1.0)

	w.waitWindowCloseButton();
	
	return 0;
}