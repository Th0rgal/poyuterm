#pragma once

#include "domains/gameData.hpp"
#include "domains/grid.hpp"
#include "views/display.hpp"

class GameManager
{
public:
    GameManager(GameData &gameData, Grid &grid, ConsoleDisplay &display);
    void start();
    void loop(int delay);

private:
    ConsoleDisplay &display;
    GameData &gameData;
    Grid &grid;
    std::vector<std::pair<int, int>> createNewPiece();
    void shiftActivePiece();
};