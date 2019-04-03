#include "Window.h"

int main(int argc, char **argv){
    Window w(201, 201); //White background color and black drawing color by default

    Point2D p1(50, 101);
    Point2D p2(150, 101);

    w.line(p1, p2, BLACK); //thickness 1.0 by default

    w.waitWindowCloseButton();

    return 0;
}