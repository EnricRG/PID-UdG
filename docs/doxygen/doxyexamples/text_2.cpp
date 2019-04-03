#include "Window.h"

int main(int argc, char **argv){
    Window w(201, 201); //White background color and black drawing color by default
	
	w.addFont("myFont", "OpenSans-Regular.ttf", 12, BLACK);

    w.text("myFont", 101, 101, "Your text goes here", TEXT_ALIGN_CENTER);

    w.waitWindowCloseButton();

    return 0;
}