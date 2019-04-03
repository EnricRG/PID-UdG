#include "Window.h"

int main(int argc, char **argv){
    Window w(201, 201); //White background color and black drawing color by default

    Point2D c(101, 75);
    w.filled_pieslice(c, 50, 60, 60, BLACK);

    w.waitWindowCloseButton();

    return 0;
}