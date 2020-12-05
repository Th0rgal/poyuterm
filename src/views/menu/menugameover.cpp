#include <stdlib.h> /* calloc() */
#include <string.h> /* strlen() */
#include <string>
#include "views/menu/menuscreen.hpp"

/**
 * Declare game over menu
 *
 * @author Valeran MAYTIE
 **/
void MenuScreen::declareMenuOver()
{
	char *choices[] = /* The menu choices */
        {
            (char *)"            Replay            ",
            (char *)"             Exit             ",
            NULL};

    /* Calculate nchoices */
    for (nChoicesOver = 0; choices[nChoicesOver]; nChoicesOver++);

    /* alloction of an iteam array for the menu */
    endIteam = (ITEM **)calloc(nChoicesOver + 1, sizeof(ITEM *));
    for (int ssChoice = 0; ssChoice < nChoicesOver; ++ssChoice)
        endIteam[ssChoice] = new_item(choices[ssChoice], NULL);

    endIteam[nChoicesOver] = (ITEM *)NULL;

    /* menu structure creation */
    gameOverMenu = new_menu((ITEM **)endIteam);

    /* symbole  on the left of selected iteam*/
    set_menu_mark(gameOverMenu, "> ");

    /* Windows Border cration */
    wBorderGameOver = newwin(8, 40, LINES / 2 - 8 / 2, COLS / 2 - 40 / 2);
    wattrset(wBorderGameOver, COLOR_PAIR(WHITEONRED));
    windowsFilling(wBorderGameOver);
    box(wBorderGameOver, 0, 0);
    windowsBorderTitle(wBorderGameOver, " Game Over ");

    wMenuGameOver = derwin(wBorderGameOver, 2, 40 - 2, 4, 2);

    set_menu_sub(gameOverMenu, wMenuGameOver);

    set_menu_fore(gameOverMenu, COLOR_PAIR(REDONWHITE));
    set_menu_back(gameOverMenu, COLOR_PAIR(WHITEONRED));

}

/**
 * Diplay game over menu
 *
 * @aparam unsigned int represent score
 * @author Valeran MAYTIE
 **/
void MenuScreen::displayMenuOver(unsigned int score)
{
	refresh();
    ScoreInMenu(score);
    post_menu(gameOverMenu);
    updateMenuOver();
}

/**
 * Update game over menu
 *
 * @author Valeran MAYTIE
 **/
void MenuScreen::updateMenuOver()
{
	touchwin(wMenuGameOver);
    wrefresh(wMenuGameOver);
    touchwin(wBorderGameOver);
    wrefresh(wBorderGameOver);
}

/**
 * Display score in menu game over
 *
 * @aparam unsigned int represent score
 * @author Valeran MAYTIE
 **/
void MenuScreen::ScoreInMenu(unsigned int score)
{
    const char *scoreString = std::to_string(score).c_str();
	mvwprintw(wBorderGameOver, 2, 5, "Score :");
	mvwprintw(wBorderGameOver, 2, 13, scoreString);

	wrefresh(wBorderGameOver);	
}