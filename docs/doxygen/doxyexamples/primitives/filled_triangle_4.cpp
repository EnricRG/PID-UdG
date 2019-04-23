#include "WindowAddon.h"

int main(int argc, char **argv){
    Window w(201, 201); //White background color and black drawing color by default

    Point2D p1(50, 50);
    Point2D p2(150, 50);
    Point2D p3(150, 150);
    w.filled_triangle(p1, p2, p3); //Using w drawing parameters (in this case, black drawing color)

    w.waitWindowCloseButton();

    return 0;
}