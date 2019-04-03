#include "Window.h"

int main(int argc, char **argv){
    Window w(201, 201); //White background color and black drawing color by default

    Point2D p1(50, 50);
    Point2D p2(150, 50);
    Point2D p3(150, 150);
    w.triangle(p1, p2, p3, BLACK); //thickness 1.0 by default

    w.waitWindowCloseButton();

    return 0;
}