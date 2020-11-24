
#include <ncurses.h>
#include <curses.h>
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

    WINDOW *gridScreen;
    int x = (6 * 6) + 2;
    int y = (12 * 3) + 2;

    gridScreen = subwin(stdscr, x, y, LINES - y - 5, COLS / 2 - x /2);
    box(gridScreen, ACS_VLINE, ACS_HLINE);

    wrefresh(gridScreen);

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

void ConsoleDisplay::setCell(int x,
                             int y,
                             Grid::PuyoType puyo)
{
    switch (puyo)
    {
    case Grid::none:
        break;

    case Grid::red:
        break;

    case Grid::green:
        break;

    case Grid::yellow:
        break;

    case Grid::blue:
        break;

    case Grid::pink:
        break;

    default:
        break;
    }
}

void ConsoleDisplay::close()
{
    endwin();

    free(gridScreen);
}