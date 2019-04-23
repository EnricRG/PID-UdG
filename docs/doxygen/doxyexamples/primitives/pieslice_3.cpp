#include "WindowAddon.h"

int main(int argc, char **argv){
    Window w(201, 201); //White background color and black drawing color by default

    w.pieslice(101, 75, 50, 60, 60, BLACK); //Using w drawing parameters (in this case, black drawing color and thickness 1.0)

    w.waitWindowCloseButton();

    return 0;
}