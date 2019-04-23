#include "WindowAddon.h"

int main(int argc, char **argv){
    Window w(201, 201); //White background color and black drawing color by default

    w.rectangle(50, 150, 150, 100); //Using w drawing parameters (in this case, black drawing color and thickness 1.0)

    w.waitWindowCloseButton();

    return 0;
}