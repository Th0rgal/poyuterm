#include "views/screen.hpp"

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
        free(window);
}