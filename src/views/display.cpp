
#include <ncurses.h>
#include "views/display.hpp"
#include <string>

bool ConsoleDisplay::start()
{
    initscr();
    int boxHeight = LINES - 2;
    // it must be superior to 0
    virtualScale = (boxHeight - boxHeight % 12) / 12;
    
    // to fix arrow keys detection
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);

    // to make getch() not blocking
    nodelay(stdscr, TRUE);
    return (COLS > 20 + 2 + 12 && virtualScale > 0);
}

void ConsoleDisplay::showError()
{
    printw("Error: your terminal is too small \nminimum cols: 44 \nminimum lines: 14");
    getch();
    close();
}

void ConsoleDisplay::setCell(int x, int y, Grid::PuyoType puyo)
{
    move(x * virtualScale, y * virtualScale);
    addch('#');
}

void ConsoleDisplay::close()
{
    endwin();
}