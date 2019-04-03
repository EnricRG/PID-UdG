#include "Window.h"

int main(int argc, char **argv){
    Window w(201, 201); //White background color and black drawing color by default

    w.filled_rounded_rectangle(50, 150, 150, 100, 10, 10, BLACK);

    w.waitWindowCloseButton();

    return 0;
}