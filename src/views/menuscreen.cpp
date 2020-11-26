#include <stdlib.h> /* calloc() */
#include <string.h> /* strlen() */
#include "views/menuscreen.hpp"
#include "controllers/inputsListener.hpp"
#include <iostream>

#define WHITEONRED 10
#define WHITEONBLUE 20
#define WHITEONBLACK 30
#define BLACKONWHITE 40
#define REDONWHITE 50

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

    char *choices[] = /* The menu choices */
        {
            (char *)"            Solo              ",
            (char *)"            Bot               ",
            (char *)"            Tetris            ",
            (char *)"            Quitter           ",
            NULL};

    /* Calculate nchoices */
    for (n_choices = 0; choices[n_choices]; n_choices++)
        ;

    /* alloction of an iteam array for the menu */
    my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
    for (ssChoice = 0; ssChoice < n_choices; ++ssChoice)
        my_items[ssChoice] = new_item(choices[ssChoice], NULL);

    my_items[n_choices] = (ITEM *)NULL;

    /* menu structure creation */
    my_menu = new_menu((ITEM **)my_items);

    /* symbole  on the left of selected iteam*/
    set_menu_mark(my_menu, "> ");

    /* Windows Border cration */
    wBorder = newwin(8, 40, LINES / 2 - 8 / 2, COLS / 2 - 40 / 2);
    registerWindow(wBorder);
    wattrset(wBorder, COLOR_PAIR(WHITEONRED));
    windowsFilling(wBorder);
    box(wBorder, 0, 0);
    windowsBorderTitle(wBorder, " option ");

    wUI = derwin(wBorder, 8 - 2, 40 - 2, 2, 2);
    registerWindow(wUI);

    set_menu_sub(my_menu, wUI);

    set_menu_fore(my_menu, COLOR_PAIR(REDONWHITE));
    set_menu_back(my_menu, COLOR_PAIR(WHITEONRED));

    /* menu display */
    post_menu(my_menu);
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

void MenuScreen::next()
{
    menu_driver(my_menu, REQ_DOWN_ITEM);
    update();
}

void MenuScreen::previous()
{
    menu_driver(my_menu, REQ_UP_ITEM);
    update();
}

int MenuScreen::select()
{
    my_choice = item_index(current_item(my_menu));
    pos_menu_cursor(my_menu);
    unpost_menu(my_menu);

    for (ssChoice = 0; ssChoice < n_choices; ++ssChoice)
        free_item(my_items[ssChoice]);

    free_menu(my_menu);

    delwin(wUI);
    delwin(wBorder);

    touchwin(stdscr);
    wrefresh(stdscr);

    return my_choice + 1;
}

void MenuScreen::update()
{
    touchwin(wUI);
    wrefresh(wUI);
    touchwin(wBorder);
    wrefresh(wBorder);
}