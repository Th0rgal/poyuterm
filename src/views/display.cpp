#include <ncurses.h>
#include <curses.h>
#include <string>
#include "views/display.hpp"
#include "views/menuscreen.hpp"
#include "views/gamescreen.hpp"

/**
 * to intialize a display
 * 
 * @author Valeran Maytié
 **/
Display::Display()
{
    initscr();

    if (LINES < 12 + 2 or COLS < 6 * 2 + 2)
    {
        printw("Error: your terminal is too small \nminimum cols: 44 \nminimum lines: 14");
        getch();
        return;
    }

    if (!has_colors())
    {
        endwin();
        printf("Error: your terminal doesn't suport colors");

        return;
    }

    // to disable cursor
    curs_set(0);

    // to fix arrow keys detection
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);

    // to disable the keystroke display
    noecho();

    use_default_colors();
    start_color();

    started = true;
}

void Display::showMenu()
{
    menu = MenuScreen();
}

void Display::showGame()
{
    game = GameScreen();
}

void Display::close()
{
    if (menu.has_value())
        (*menu).close();

    if (game.has_value())
        (*game).close();
}