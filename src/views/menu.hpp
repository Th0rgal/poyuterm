#pragma once

#include <curses.h>
#include <menu.h>


class MenuManager
{
public:
	MenuManager();
	int runMenu();

private:

    int key;
    ITEM **my_items;
    MENU *my_menu;

    WINDOW *wUI;
    WINDOW *wBorder;

    int n_choices;
    int ssChoice;
    int my_choice = -1;
	void wCenterTitle(WINDOW *pwin, const char * title);
	void wclrscr(WINDOW * pwin);
};