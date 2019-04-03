#include "Window.h"

int main(int argc, char **argv){
    Window w(201, 201); //White background color and black drawing color by default

    w.filled_ellipse(101, 101, 35, 25, BLACK);

    w.waitWindowCloseButton();

    return 0;
}