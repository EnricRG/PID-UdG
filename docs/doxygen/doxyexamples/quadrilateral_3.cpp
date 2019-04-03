#include "Window.h"

int main(int argc, char **argv){
	Window w(201, 201); //White background color and black drawing color by default

	w.quadrilateral(50, 50, 40, 110, 120, 150, 100, 55); //Using w drawing parameters (in this case, black drawing color and thickness 1.0)

	w.waitWindowCloseButton();

	return 0;
}