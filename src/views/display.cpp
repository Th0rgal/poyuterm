
#include <ncurses.h>
#include <curses.h>
#include "views/display.hpp"
#include <string>

#define COLOR_PINK 5

ConsoleDisplay::ConsoleDisplay()
{
}

bool ConsoleDisplay::start()
{
    initscr();

    if (LINES < 12+2 or COLS < 6*2 +2) {
        showError();
        return false;
    }
    
    int boxHeight = LINES - 2;
    // it must be superior to 0
    virtualScale = (boxHeight - boxHeight % 12) / 12;

    // to fix arrow keys detection
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);

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
    int x = (6 * virtualScale * 2) + 2;
    int y = (12 * virtualScale) + 2;

    gridScreen = subwin(stdscr, x, y, LINES - y - 5, COLS / 2 - x / 2);
    box(gridScreen, ACS_VLINE, ACS_HLINE);

    wrefresh(gridScreen);

    //mvwprintw(stdscr, 0, 0, "aaaaaa");
    setCell(1, 12, Grid::none);
    setCell(2, 12, Grid::red);
    setCell(3, 12, Grid::green);
    setCell(4, 12, Grid::yellow);
    setCell(5, 12, Grid::blue);
    setCell(6, 12, Grid::pink);

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
    x = 6 * x + COLS / 2 - 24;
    y = 3 * y + LINES - 45;

    init_color(COLOR_PINK, 238, 66, 244);
    init_pair(Grid::red, -1, COLOR_RED);
    init_pair(Grid::green, -1, COLOR_GREEN);
    init_pair(Grid::yellow, -1, COLOR_YELLOW);
    init_pair(Grid::blue, -1, COLOR_BLUE);
    init_pair(Grid::pink, -1, COLOR_PINK);
    init_pair(Grid::none, -1, -1);

    attron(COLOR_PAIR(puyo));
    for (int i = y; i < y + 3; i++)
    {
        mvwprintw(stdscr, i, x, "      ");
    }
    attroff(COLOR_PAIR(puyo));
}

void ConsoleDisplay::close()
{
    endwin();

    free(gridScreen);
}