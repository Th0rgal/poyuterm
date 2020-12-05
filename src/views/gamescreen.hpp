#pragma once

#include "models/grid.hpp"
#include <string>
#include <ncurses.h>
#include "views/music/music.hpp"

class GameScreen
{
public:
    GameScreen();
    void setCell(int x, int y, Grid::PuyoType puyo);
    void refreshDiff(
        std::vector<std::vector<Grid::PuyoType>> &snapshot,
        Grid &grid);
    void close();
    void displayScore(unsigned int score);

private:
    WINDOW *scoreWin;
    int virtualScale;
    std::string puyoLine;
    int gridWidth;
    int gridHeight;
};