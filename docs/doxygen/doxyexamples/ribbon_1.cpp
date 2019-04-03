#include "Window.h"

int main(int argc, char **argv) {
	Window w(201, 201);

	float points[8] = { 
		100, 100, 
		115, 130, 
		110, 145,
		95, 150
	};
	
	w.ribbon(points, 4, BLACK); //thickness 1.0 by default

	w.waitWindowCloseButton();
	
	return 0;
}