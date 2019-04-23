#include "WindowAddon.h"

int main(int argc, char **argv){
    Window w(201, 201); //White background color and black drawing color by default

    Point2D p1(50, 101);
    Point2D p2(150, 101);

    w.line(p1, p2); //Using w drawing parameters (in this case, black drawing color and thickness 1.0)

    w.waitWindowCloseButton();

    return 0;
}