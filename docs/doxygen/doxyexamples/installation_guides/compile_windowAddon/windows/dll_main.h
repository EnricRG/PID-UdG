#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>

//Window Add-on main header file
#include "windowAddon/Window.h"

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

#endif // __MAIN_H__
