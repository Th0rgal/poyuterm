
#include <ncurses.h>
#include "views/display.hpp"
#include <string>

ConsoleDisplay::ConsoleDisplay(InputsListener &inputsListenerReference)
{
    inputsListener = inputsListenerReference;
}

void ConsoleDisplay::setCell(int x, int y, Grid::PuyoType puyo)
{
    move(x * virtualScale, y * virtualScale);
    addch('#');
}

void ConsoleDisplay::start()
{
    initscr();
    int boxHeight = LINES - 2;
    virtualScale = (boxHeight - boxHeight % 12) / 12; // it must be superior to 0

    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);
    if (COLS > 20 + 2 + 12 && virtualScale > 0)
    {
        int inputCode;
        do
        {
            inputCode = getch();
            inputsListener.onKeyPressed(inputCode);
        } while (inputCode != KEY_SDL);
        endwin();
    }
    else
    {
        printw("Error: your terminal is too small \nminimum cols: 44 \nminimum lines: 14");

        getch();
        endwin();
    }
}