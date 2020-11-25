#pragma once

#include "domains/gameData.hpp"
#include "domains/grid.hpp"
#include "views/display.hpp"
#include "views/menu.hpp"
#include <random>

class GameManager
{
public:
    GameManager(GameData &gameData,
                Grid &grid);
    void start();
    void loop(long delay);

private:
    GameData &gameData;
    Grid &grid;
    ConsoleDisplay display = ConsoleDisplay();
    MenuManager menu = MenuManager();
    std::random_device rd;
    std::mt19937 gen;

    std::vector<Puyo> createNewPiece();
    void shiftActivePiece();
    std::size_t random_index(std::size_t lower,
                             std::size_t higher);
};
