#include <stdlib.h> /* calloc() */
#include <string.h> /* strlen() */
#include "views/menu/menuscreen.hpp"

void MenuScreen::declareMenuStart()
{
	char *choices[] = /* The menu choices */
        {
            (char *)"            Solo              ",
            (char *)"            Replay            ",
            (char *)"            Tetrix            ",
            (char *)"            Quitter           ",
            NULL};

    /* Calculate nchoices */
    for (numberChoicesStart = 0; choices[numberChoicesStart]; numberChoicesStart++);

    /* alloction of an iteam array for the menu */
    iteamStart = (ITEM **)calloc(numberChoicesStart + 1, sizeof(ITEM *));
    for (int ssChoice = 0; ssChoice < numberChoicesStart; ++ssChoice)
        iteamStart[ssChoice] = new_item(choices[ssChoice], NULL);

    iteamStart[numberChoicesStart] = (ITEM *)NULL;

    /* menu structure creation */
    menuStart = new_menu((ITEM **)iteamStart);

    /* symbole  on the left of selected iteam*/
    set_menu_mark(menuStart, "> ");

    /* Windows Border cration */
    wBorderStart = newwin(8, 40, LINES / 2 - 8 / 2, COLS / 2 - 40 / 2);
    wattrset(wBorderStart, COLOR_PAIR(WHITEONRED));
    windowsFilling(wBorderStart);
    box(wBorderStart, 0, 0);
    windowsBorderTitle(wBorderStart, " option ");

    wMenuStart = derwin(wBorderStart, 8 - 2, 40 - 2, 2, 2);

    set_menu_sub(menuStart, wMenuStart);

    set_menu_fore(menuStart, COLOR_PAIR(REDONWHITE));
    set_menu_back(menuStart, COLOR_PAIR(WHITEONRED));

}

void MenuScreen::updateMenuStart()
{
    touchwin(wMenuStart);
    wrefresh(wMenuStart);
    touchwin(wBorderStart);
    wrefresh(wBorderStart);
}

void MenuScreen::displayMenuStart()
{
    refresh();
    post_menu(menuStart);
    updateMenuStart();
}