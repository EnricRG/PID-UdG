#include "Window.h"

int main(int argc, char **argv){
    Window w(201, 201); //White background color and black drawing color by default
	
	w.arc(101, 75, 50, 0, 180, BLACK); //thickness 1.0 by default

    w.waitWindowCloseButton();

    return 0;
}