#include "WindowAddon.h"

int main(int argc, char **argv){
    Window w(201, 201); //White background color and black drawing color by default

    w.filled_circle(101, 101, 35); //Using w drawing parameters (in this case, black drawing color)

    w.waitWindowCloseButton();

    return 0;
}