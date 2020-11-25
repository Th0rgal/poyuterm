#pragma once

#include <curses.h>
#include <menu.h>


class ManuManager
{
public:
	ManuManager();
	int runMenu(WINDOW *wParent, int height, int width, int y, int x);

private:
	
    int c;
    ITEM **my_items;
    MENU *my_menu;

    WINDOW *wUI;
    WINDOW *wBorder;

    int n_choices;
    int ssChoice;
    int my_choice = -1;
	void wCenterTitle(WINDOW *pwin, const char * title);
	void wclrscr(WINDOW * pwin);
	bool initColors();
};