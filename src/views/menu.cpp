#include <curses.h>
#include <menu.h>
#include <stdlib.h> /* calloc() */
#include <string.h> /* strlen() */

#include "menu.hpp"

#define WHITEONRED 1
#define WHITEONBLUE 2
#define WHITEONBLACK 3
#define BLACKONWHITE 4
#define REDONWHITE 5

void ManuManager::wCenterTitle(WINDOW *pwin, const char * title)
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


void ManuManager::wclrscr(WINDOW * pwin)
{
    int y, x, maxy, maxx;
    getmaxyx(pwin, maxy, maxx);
    for(y=0; y < maxy; y++)
        for(x=0; x < maxx; x++)
            mvwaddch(pwin, y, x, ' ');
}

bool ManuManager::initColors()
{
    if(has_colors())
    {
        use_default_colors();
        start_color();
        init_pair(WHITEONRED, COLOR_WHITE, COLOR_RED);
        init_pair(WHITEONBLUE, COLOR_WHITE, COLOR_BLUE);
        init_pair(REDONWHITE, COLOR_RED, COLOR_WHITE);
        return(true);
    }
    else
        return(false);
}


int ManuManager::runMenu(WINDOW *wParent, int height, int width, int y, int x)
{
    char *choices[] =           /* The menu choices */
            {
                        (char*)"            Solo              ",
                        (char*)"            Duo               ",
                        (char*)"            Bot               ",
                        (char*)"            Tetris            ",
                        (char*)"            Quitter           ",
            NULL
            };
    /* Calculate nchoices */
    for(n_choices=0; choices[n_choices]; n_choices++);

    /* alloction of an iteam array for the menu */
   	my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
    for(ssChoice = 0; ssChoice < n_choices; ++ssChoice)
		my_items[ssChoice] = new_item(choices[ssChoice], NULL);
    
    my_items[n_choices] = (ITEM *)NULL;

    /* menu structure creation */
    my_menu = new_menu((ITEM **)my_items);

    /* symbole  on the left of selected iteam*/
    set_menu_mark(my_menu, "> ");

    /* Windows Border cration */
    wBorder = newwin(height, width, LINES / 2 - height / 2, COLS / 2 - width / 2);
    wattrset(wBorder, COLOR_PAIR(WHITEONRED));
    wclrscr(wBorder); 
    box(wBorder, 0, 0);
    wCenterTitle(wBorder, "Option de jeu a choisir");

    /* SET UP WINDOW FOR THE MENU'S USER INTERFACE */
    wUI = derwin(wBorder, height-2, width-2, 2, 2);

    /* ASSOCIATE THESE WINDOWS WITH THE MENU */
    set_menu_sub(my_menu, wUI);

    /* MATCH MENU'S COLORS TO THAT OF ITS WINDOWS */
    set_menu_fore(my_menu, COLOR_PAIR(REDONWHITE));
    set_menu_back(my_menu, COLOR_PAIR(WHITEONRED));

    keypad(wUI, TRUE);
    noecho();
    curs_set(0);

    /* menu display */
    post_menu(my_menu);

    touchwin(wBorder);
    wrefresh(wBorder);  

    /* Key pressed */
    while(my_choice == -1)
    {
        touchwin(wUI);
        wrefresh(wUI);
        c = getch();
        switch(c)
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

    /* FREE ALL ALLOCATED MENU AND ITEM RESOURCES */
    unpost_menu(my_menu);
    
    for(ssChoice = 0; ssChoice < n_choices; ++ssChoice)
        free_item(my_items[ssChoice]);
    
    free_menu(my_menu);

    delwin(wUI);
    delwin(wBorder);
    
    /* REPAINT THE CALLING SCREEN IN PREPARATION FOR RETURN */
    touchwin(wParent);
    wrefresh(wParent);

    /* return numbor of choice*/
    return(my_choice);
}