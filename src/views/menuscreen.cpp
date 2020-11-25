#include <stdlib.h> /* calloc() */
#include <string.h> /* strlen() */
#include "views/menuscreen.hpp"

#define WHITEONRED 1
#define WHITEONBLUE 2
#define WHITEONBLACK 3
#define BLACKONWHITE 4
#define REDONWHITE 5

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
            (char *)"            Duo               ",
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
    wattrset(wBorder, COLOR_PAIR(WHITEONRED));
    windowsFilling(wBorder);
    box(wBorder, 0, 0);
    windowsBorderTitle(wBorder, " option ");

    wUI = derwin(wBorder, 8 - 2, 40 - 2, 2, 2);

    set_menu_sub(my_menu, wUI);

    set_menu_fore(my_menu, COLOR_PAIR(REDONWHITE));
    set_menu_back(my_menu, COLOR_PAIR(WHITEONRED));

    /* menu display */
    post_menu(my_menu);

    touchwin(wBorder);
    wrefresh(wBorder);

    /* Key pressed */
    while (my_choice == -1)
    {
        touchwin(wUI);
        wrefresh(wUI);
        key = getch();
        switch (key)
        {
        case KEY_DOWN:
            menu_driver(my_menu, REQ_DOWN_ITEM);
            break;
        case KEY_UP:
            menu_driver(my_menu, REQ_UP_ITEM);
            break;
        case '\n':
            my_choice = item_index(current_item(my_menu));
            pos_menu_cursor(my_menu);
            break;
        }
    }

    unpost_menu(my_menu);

    for (ssChoice = 0; ssChoice < n_choices; ++ssChoice)
        free_item(my_items[ssChoice]);

    free_menu(my_menu);

    delwin(wUI);
    delwin(wBorder);

    touchwin(stdscr);
    wrefresh(stdscr);

    /* return numbor of choice*/
    //return (my_choice);
}

void MenuScreen::windowsBorderTitle(WINDOW *pwin, const char *title)
{
    int x, maxy, maxx, stringsize;
    getmaxyx(pwin, maxy, maxx);
    stringsize = 4 + strlen(title);
    x = (maxx - stringsize)/2;
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