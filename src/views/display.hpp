#pragma once

#include <string>
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
    bool started = false;

private:
    int virtualScale;
    std::string puyoLine;
    int width;
	int height;
};