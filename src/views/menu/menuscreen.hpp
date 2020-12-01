#pragma once

#include <menu.h>

#define WHITEONRED 10
#define WHITEONBLUE 20
#define WHITEONBLACK 30
#define BLACKONWHITE 40
#define REDONWHITE 50

class MenuScreen
{
public:
    MenuScreen();
    void next(int state);
    void previous(int state);
    int select(int state);
    void close();
    void displayMenuStart();
    void displayMenuOver(unsigned int score);

private:
    int key;
    void windowsBorderTitle(WINDOW *pwin, const char *title);
    void windowsFilling(WINDOW *pwin);
    int my_choice = -1;

    /* Menu Start */
    ITEM **iteamStart;
    MENU *menuStart;

    WINDOW *wMenuStart;
    WINDOW *wBorderStart;

    int numberChoicesStart;
    void declareMenuStart();
    void updateMenuStart();

    /* menu End */

    ITEM **endIteam;
    MENU * gameOverMenu;

    WINDOW *wMenuGameOver;
    WINDOW *wBorderGameOver;

    int nChoicesOver; 
    void declareMenuOver();
    void updateMenuOver();
    void ScoreInMenu(unsigned int score);

};