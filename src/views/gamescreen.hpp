#pragma once

#include "models/grid.hpp"
#include <string>

class GameScreen
{
public:
    GameScreen();
    void setCell(int x, int y, Grid::PuyoType puyo);
    void refreshDiff(
        std::vector<std::vector<Grid::PuyoType>> &snapshot,
        Grid &grid);
    void close();

private:
    int virtualScale;
    std::string puyoLine;
    int gridWidth;
    int gridHeight;
};