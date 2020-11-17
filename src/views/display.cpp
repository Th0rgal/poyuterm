
#include <ncurses.h>
#include "views/display.hpp"

ConsoleDisplay::ConsoleDisplay(InputsListener &inputsListenerReference)
{
    inputsListener = inputsListenerReference;
}

void ConsoleDisplay::start()
{
    initscr();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);
    int inputCode;
    do
    {
        inputCode = getch();
        inputsListener.onKeyPressed(inputCode);
    } while (inputCode != KEY_SDL);

    endwin();
}