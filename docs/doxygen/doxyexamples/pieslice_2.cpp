#include "WindowAddon.h"

int main(int argc, char **argv){
    Window w(201, 201); //White background color and black drawing color by default

    Point2D c(101, 75);
    w.pieslice(c, 50, 60, 60, BLACK); //thickness 1.0 by default

    w.waitWindowCloseButton();

    return 0;
}