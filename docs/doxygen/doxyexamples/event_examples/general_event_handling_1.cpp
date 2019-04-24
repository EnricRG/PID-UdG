#include <iostream>
#include "WindowAddon.h"

int main()
{
    Window w(300, 300);

    bool end = false;
    WindowEvent event;

    while(!end){
        event  = w.waitWindowEvent();

        if(event.type == WINDOW_EVENT_DISPLAY_CLOSE){
            end = true; //finish the program
        }
        else if(event.type == WINDOW_EVENT_MOUSE_BUTTON_DOWN){
            std::cout << "Mouse button was pressed" << std::endl;
        }
        else if(event.type == WINDOW_EVENT_KEY_DOWN){
            std::cout << "Keyboard key was pressed" << std::endl;
        }
        else{
            std::cout << "Another type of event" << std::endl;
        }
    }

    return 0;
}