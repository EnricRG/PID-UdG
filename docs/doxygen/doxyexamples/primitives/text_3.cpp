#include "WindowAddon.h"

int main(int argc, char **argv){
    Window w(201, 201); //White background color and black drawing color by default
	
	Font f("OpenSans-Regular.ttf", BLACK, 12, 0);

    Point2D c(101, 101);
    w.text(f, c, "Your text goes here", TEXT_ALIGN_CENTER);

    w.waitWindowCloseButton();

    return 0;
}