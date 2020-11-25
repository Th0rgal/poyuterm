#pragma once

#include <menu.h>
#include "views/screen.hpp"

class MenuScreen : public Screen
{
public:
    MenuScreen();
    void next();
    void previous();
    int select();
    
private:
    int key;
    ITEM **my_items;
    MENU *my_menu;

    WINDOW *wUI;
    WINDOW *wBorder;

    int n_choices;
    int ssChoice;
    int my_choice = -1;
    void windowsBorderTitle(WINDOW *pwin, const char *title);
    void windowsFilling(WINDOW *pwin);
    void update();

};