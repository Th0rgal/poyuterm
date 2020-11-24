#include <ncurses.h>
#include <curses.h>
#include "views/display.hpp"
#include <string>

#define COLOR_RED 1
#define COLOR_GREEN 2
#define COLOR_YELLOW 3
#define COLOR_BLUE 4
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
    for(int i = 0; i < virtualScale; i++){
        puyoLine += "  ";
    }
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
    width = (6 * virtualScale * 2) + 2;
    height = (12 * virtualScale) + 2;

    gridScreen = subwin(stdscr, width, height, LINES - height, COLS / 2 - width / 2);
    box(gridScreen, ACS_VLINE, ACS_HLINE);

    wrefresh(gridScreen);

    //mvwprintw(stdscr, 0, 0, "aaaaaa");
    for(int i = 0; i < 12; i++){
        setCell((0 + i) % 6, i, Grid::none);
        setCell((1 + i) % 6, i, Grid::red);
        setCell((2 + i) % 6, i, Grid::green);
        setCell((3 + i) % 6, i, Grid::yellow);
        setCell((4 + i) % 6, i, Grid::blue);
        setCell((5 + i) % 6, i, Grid::pink);
    }

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
    x = 1 + (x) * virtualScale * 2 + COLS / 2 - width / 2;
    y = 1 + (y) * virtualScale + LINES - height;

    init_color(COLOR_RED, 2550, 0, 0);
    init_color(COLOR_GREEN, 0, 2550, 0);
    init_color(COLOR_YELLOW, 2550, 2550, 0);
    init_color(COLOR_BLUE, 0, 0, 2550);
    init_color(COLOR_PINK, 2550, 200, 1470);

    init_pair(Grid::red, -1, COLOR_RED);
    init_pair(Grid::green, -1, COLOR_GREEN);
    init_pair(Grid::yellow, -1, COLOR_YELLOW);
    init_pair(Grid::blue, -1, COLOR_BLUE);
    init_pair(Grid::pink, -1, COLOR_PINK);
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