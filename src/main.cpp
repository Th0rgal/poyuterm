#include <ncurses.h>
#include "game/game.hpp"

using namespace std;

int main() {

    initscr();              // Initialise la structure WINDOW et autres paramètres 
    printw("Hello World");  // Écrit Hello World à l'endroit où le curseur logique est positionné
    game::loop();
    refresh();              // Rafraîchit la fenêtre courante afin de voir le message apparaître
    getch();                // On attend que l'utilisateur appui sur une touche pour quitter
    endwin();               // Restaure les paramètres par défaut du terminal
    
    return 0;
}