#pragma once

#include "domains/grid.hpp"
#include "views/screen.hpp"

class GameScreen : public Screen
{
public:
    GameScreen();
    void setCell(int x, int y, Grid::PuyoType puyo);

private:
    int virtualScale;
    std::string puyoLine;
    int gridWidth;
    int gridHeight;
};