#pragma once

#include "models/gameData.hpp"
#include "models/grid.hpp"
#include "views/display.hpp"
#include "controllers/parser.hpp"
#include <random>

class GameManager
{
public:
    GameManager(GameData gameData,
                Grid grid,
                Parser &parser);
    void start();
    void loop(long delay);

private:
    GameData &gameData;
    Grid &grid;
    Parser &parser;
    Display display = Display();
    std::random_device rd;
    std::mt19937 gen;

    void puyoLoop(long delay);
    void tetrixLoop(long delay);

    std::vector<Puyo> createNewPiece();
    void shiftActivePiece();
    std::size_t random_index(std::size_t lower,
                             std::size_t higher);
};
