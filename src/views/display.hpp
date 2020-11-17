#pragma once

#include "domains/grid.hpp"

class ConsoleDisplay
{
public:
    bool start();
    void showError();
    void setCell(int x, int y, Grid::PuyoType puyo);
    void close();

private:
    int virtualScale;
};