#include "Window.h"

int main(int argc, char **argv){
    Window w(201, 201); //White background color and black drawing color by default
	
	w.text(101, 101, "Your text goes here", TEXT_ALIGN_CENTER); //Using w drawing parameters (in this case, the default font)

    w.waitWindowCloseButton();

    return 0;
}