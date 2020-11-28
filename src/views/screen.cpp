#include "views/screen.hpp"
#include <iostream>

/**
 * to close the display
 * 
 * @author Valeran Maytié
 **/
void Screen::registerWindow(WINDOW *window)
{
    windows.push_back(window);
}

/**
 * to close the display
 * 
 * @author Valeran Maytié
 **/
void Screen::close()
{
    endwin();
    for (WINDOW *window : windows)
    {
        free(window);
    }
}