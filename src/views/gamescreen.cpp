#include "views/gamescreen.hpp"
#include "views/music/music.hpp"
#include <ncurses.h>
#include <string>

/**
 * Declare a Windows for game and the window for score
 *
 * @author Valeran MAYTIE
 * @confidence 3 : impossible to test display
 **/

GameScreen::GameScreen()
{

    int boxHeight = LINES - 2;
    // it must be superior to 0
    virtualScale = (boxHeight - boxHeight % 12) / 12;
    for (int i = 0; i < virtualScale; i++)
        puyoLine += "  ";

    gridWidth = (6 * virtualScale * 2) + 2;
    gridHeight = (12 * virtualScale) + 2;
    WINDOW *gridScreen = subwin(stdscr, gridWidth, gridHeight,
                                LINES - gridHeight, COLS / 2 - gridWidth / 2);
    box(gridScreen, ACS_VLINE, ACS_HLINE);
    wrefresh(gridScreen);
    scoreWin = subwin(stdscr, 4, 11, LINES - gridHeight, COLS / 2 + gridWidth / 2);
    wborder(scoreWin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(scoreWin);
}

/**
 * to display a cell at a specific location with the right color
 * @param int x position of the cell on the virtual x axis
 * @param int y position of the cell on the virtual y axis
 * @param Grid::PuyoType type of the Puyo (affects its color)
 * 
 * @author Valeran Maytié
 * @confidence 3 : impossible to test display
 **/
void GameScreen::setCell(int x,
                         int y,
                         Grid::PuyoType type)
{
    x = 1 + (x)*virtualScale * 2 + COLS / 2 - gridWidth / 2;
    y = 1 + (y)*virtualScale + LINES - gridHeight;

    init_pair(Grid::red, -1, COLOR_RED);
    init_pair(Grid::green, -1, COLOR_GREEN);
    init_pair(Grid::yellow, -1, COLOR_YELLOW);
    init_pair(Grid::blue, -1, COLOR_BLUE);
    init_pair(Grid::pink, -1, COLOR_MAGENTA);
    init_pair(Grid::none, -1, -1);

    attron(COLOR_PAIR(type));
    for (int i = y; i < y + virtualScale; i++)
    {
        mvwprintw(stdscr, i, x, puyoLine.c_str());
    }
    attroff(COLOR_PAIR(type));
}

/**
 * refresh Grid in the terminal
 *
 * @author Valeran MAYTIE
 * @confidence 3 : impossible to test display
 **/
void GameScreen::refreshDiff(std::vector<std::vector<Grid::PuyoType>> &snapshot,
                             Grid &grid)
{
    for (std::size_t x = 0; x < grid.width(); x++)
        for (std::size_t y = 0; y < grid.height(); y++)
        {
            if (snapshot[x][y] != grid.content[x][y])
                setCell(x, y, grid.content[x][y]);
        }
}

/**
 * Close ncurses
 *
 * @author Valeran MAYTIE
 * @confidence 3 : impossible to test display
 **/
void GameScreen::close()
{
    endwin();
}

/**
 * Diplay Score right of the window
 *
 * @author Valeran MAYTIE
 * @confidence 3 : impossible to test display
 **/
void GameScreen::displayScore(unsigned int score)
{
    mvwprintw(scoreWin, 1, 1, "  [score]");
    std::string scoreText = std::to_string(score);
    std::string spacing((12 - scoreText.size())/2, ' ');
    mvwprintw(scoreWin, 2, 1, (spacing + scoreText).c_str());
    wrefresh(scoreWin);
}