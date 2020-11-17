#pragma once

#include "domains/gameData.hpp"
#include "domains/grid.hpp"
#include "views/display.hpp"

class GameManager
{
public:
    GameManager(GameData &gameData, Grid &grid, ConsoleDisplay &display);
    void start();
    void applyMechanics();

private:
    ConsoleDisplay display;
    GameData gameData;
    Grid grid;
};