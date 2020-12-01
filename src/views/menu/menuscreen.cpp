#include <stdlib.h> /* calloc() */
#include <string.h> /* strlen() */
#include "views/menu/menuscreen.hpp"

MenuScreen::MenuScreen()
{
    if (has_colors())
    {
        use_default_colors();
        start_color();
        init_pair(WHITEONRED, COLOR_WHITE, COLOR_RED);
        init_pair(WHITEONBLUE, COLOR_WHITE, COLOR_BLUE);
        init_pair(REDONWHITE, COLOR_RED, COLOR_WHITE);
    }

    declareMenuStart();
    declareMenuOver();
}


void MenuScreen::windowsBorderTitle(WINDOW *pwin, const char *title)
{
    int x, maxy, maxx, stringsize;
    getmaxyx(pwin, maxy, maxx);
    stringsize = 4 + strlen(title);
    x = (maxx - stringsize) / 2;
    mvwaddch(pwin, 0, x, ACS_RTEE);
    waddch(pwin, ' ');
    waddstr(pwin, title);
    waddch(pwin, ' ');
    waddch(pwin, ACS_LTEE);
}

void MenuScreen::windowsFilling(WINDOW *pwin)
{
    int y, x, maxy, maxx;
    getmaxyx(pwin, maxy, maxx);
    for (y = 0; y < maxy; y++)
        for (x = 0; x < maxx; x++)
            mvwaddch(pwin, y, x, ' ');
}

void MenuScreen::next(int state)
{
    if(state == 1){
        menu_driver(menuStart, REQ_DOWN_ITEM);
        updateMenuStart();
    } else {
        menu_driver(gameOverMenu, REQ_DOWN_ITEM);
        updateMenuOver();
    }
}

void MenuScreen::previous(int state)
{
    if(state == 1){
        menu_driver(menuStart, REQ_UP_ITEM);
        updateMenuStart();
    } else {
        menu_driver(gameOverMenu, REQ_UP_ITEM);
        updateMenuOver();
    }
}

int MenuScreen::select(int state)
{   
    if (state == 1) {
        my_choice = item_index(current_item(menuStart));
        pos_menu_cursor(menuStart);
        unpost_menu(menuStart);

        for (int ssChoice = 0; ssChoice < numberChoicesStart; ++ssChoice)
            free_item(iteamStart[ssChoice]);

        delwin(wMenuStart);
        delwin(wBorderStart);

    } else {
        my_choice = item_index(current_item(gameOverMenu));
        pos_menu_cursor(gameOverMenu);
        unpost_menu(gameOverMenu);

        for (int ssChoice = 0; ssChoice < nChoicesOver; ++ssChoice)
            free_item(endIteam[ssChoice]);

        delwin(wMenuGameOver);
        delwin(wBorderGameOver);
    }

    touchwin(stdscr);
    wrefresh(stdscr);

    return my_choice;
}

void MenuScreen::close()
{
    endwin();
    free(menuStart);
    free(gameOverMenu);
}