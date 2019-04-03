#include "WindowAddon.h"

int main(int argc, char **argv){
    Window w(201, 201); //White background color and black drawing color by default

    Point2D c(101, 101);
    w.filled_ellipse(c, 35, 25, BLACK);

    w.waitWindowCloseButton();

    return 0;
}