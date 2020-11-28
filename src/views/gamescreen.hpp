#pragma once

#include "models/grid.hpp"
#include "views/screen.hpp"

class GameScreen : public Screen
{
public:
    GameScreen();
    void setCell(int x, int y, Grid::PuyoType puyo);
    void refreshDiff(
        std::vector<std::vector<Grid::PuyoType>> &snapshot,
        Grid &grid);

private:
    int virtualScale;
    std::string puyoLine;
    int gridWidth;
    int gridHeight;
};