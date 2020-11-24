#pragma once

#include <ncurses.h>
#include "domains/grid.hpp"

class ConsoleDisplay
{
public:
	WINDOW * gridScreen;
    bool start();
    void showError();
    void setCell(int x, int y, Grid::PuyoType puyo);
    void close();
    ConsoleDisplay();

private:
    int virtualScale;
};