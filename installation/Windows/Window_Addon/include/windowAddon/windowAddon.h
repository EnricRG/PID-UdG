// Version 1.1

#ifndef __WINDOWADDON_H__
#define __WINDOWADDON_H__

#ifdef _WIN32 //Windows 32 and 64 bits
    #include <windows.h>

    #ifdef BUILD_DLL
        #define DLL_EXPORT __declspec(dllexport)
    #else
        #define DLL_EXPORT __declspec(dllimport)
    #endif
#endif

#include "windowAddon/Window.h" //Window Add-on main header file
#include "windowAddon/Drawables.h"

#endif // __WINDOWADDON_H__
