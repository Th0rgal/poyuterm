#include <ncurses.h>
#include <curses.h>
#include "views/display.hpp"
#include <string>

ConsoleDisplay::ConsoleDisplay()
{
}

bool ConsoleDisplay::start()
{
    initscr();

    if (LINES < 12 + 2 or COLS < 6 * 2 + 2)
    {
        showError();
        return false;
    }

    int boxHeight = LINES - 2;
    // it must be superior to 0
    virtualScale = (boxHeight - boxHeight % 12) / 12;
    for (int i = 0; i < virtualScale; i++)
    {
        puyoLine += "  ";
    }
    // to fix arrow keys detection
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);

    // to disable the keystroke display
    noecho();

    // to make getch() not blocking
    nodelay(stdscr, TRUE);

    if (!has_colors())
    {
        endwin();
        printf("Error: your terminal doesn't suport colors");
        return false;
    }
    use_default_colors();
    start_color();

    WINDOW *gridScreen;
    width = (6 * virtualScale * 2) + 2;
    height = (12 * virtualScale) + 2;

    gridScreen = subwin(stdscr, width, height, LINES - height, COLS / 2 - width / 2);
    box(gridScreen, ACS_VLINE, ACS_HLINE);

    wrefresh(gridScreen);

    return (COLS > 20 + 2 + 12 && virtualScale > 0);
}

void ConsoleDisplay::showError()
{
    printw("Error: your terminal is too small \nminimum cols: 44 \nminimum lines: 14");
    getch();
}

void ConsoleDisplay::setCell(int x,
                             int y,
                             Grid::PuyoType puyo)
{
    x = 1 + (x)*virtualScale * 2 + COLS / 2 - width / 2;
    y = 1 + (y)*virtualScale + LINES - height;

    init_pair(Grid::red, -1, COLOR_RED);
    init_pair(Grid::green, -1, COLOR_GREEN);
    init_pair(Grid::yellow, -1, COLOR_YELLOW);
    init_pair(Grid::blue, -1, COLOR_BLUE);
    init_pair(Grid::pink, -1, COLOR_MAGENTA);
    init_pair(Grid::none, -1, -1);

    attron(COLOR_PAIR(puyo));
    for (int i = y; i < y + virtualScale; i++)
    {
        mvwprintw(stdscr, i, x, puyoLine.c_str());
    }
    attroff(COLOR_PAIR(puyo));
}

void ConsoleDisplay::close()
{
    endwin();

    free(gridScreen);
}