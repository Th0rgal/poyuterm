#pragma once

#include "domains/gameData.hpp"
#include "domains/grid.hpp"
#include "views/display.hpp"
#include <random>

class GameManager
{
public:
    GameManager(GameData &gameData, Grid &grid, ConsoleDisplay &display);
    void start();
    void loop(long delay);

private:
    GameData &gameData;
    Grid &grid;
    ConsoleDisplay &display;
    std::random_device rd;
    std::mt19937 gen;

    std::vector<std::pair<std::size_t, std::size_t>> createNewPiece();
    void shiftActivePiece();
    std::size_t random_index(std::size_t lower, std::size_t higher);
};
