
#include <ncurses.h>
#include "views/display.hpp"

ConsoleDisplay::ConsoleDisplay(InputsListener &inputsListener)
{
}

void ConsoleDisplay::start()
{
    initscr();
    int inputCode;
    do
    {
        inputCode = getch();
    } while (inputCode != 113); // q to exit
    endwin();
}