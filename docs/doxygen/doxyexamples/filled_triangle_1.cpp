#include "Window.h"

int main(int argc, char **argv){
    Window w(201, 201); //White background color and black drawing color by default

    w.filled_triangle(50, 50, 150, 50, 150, 150, BLACK);

    w.waitWindowCloseButton();

    return 0;
}