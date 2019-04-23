#include "WindowAddon.h"

int main(int argc, char **argv) {
	Window w(201, 201);

	float points[8] = {
		90, 80,
		110, 80,
		120, 130,
		80, 130
	};

	w.polygon(points, 4, BLACK, 1, LINE_JOIN_NONE); //miter_limit is 0 by default

	w.waitWindowCloseButton();
	
	return 0;
}