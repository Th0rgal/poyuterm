#pragma once

#include "controllers/gameManager.hpp"
#include "domains/grid.hpp"

class ConsoleDisplay
{
public:
    ConsoleDisplay(InputsListener &inputsListener);
    void setCell(int x, int y, Grid::PuyoType puyo);
    void start();

private:
    int virtualScale;
    InputsListener inputsListener;
};