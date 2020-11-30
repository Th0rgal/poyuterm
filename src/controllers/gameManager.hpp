#pragma once

#include "models/gameData.hpp"
#include "models/grid.hpp"
#include "views/display.hpp"
#include "controllers/io/parser.hpp"
#include <random>

class GameManager
{
public:
    GameManager(Parser &parser);
    void start();
    void loop(long delay);

private:
    GameData _gameData{};
    Display _display{};
    Grid _grid{std::vector<std::vector<Grid::PuyoType>>(6, std::vector<Grid::PuyoType>(12))};
    Parser &parser;
    std::random_device rd;
    std::mt19937 gen;

    void puyoLoop(long delay);
    void simulationLoop(long delay);
    void tetrixLoop(long delay);

    ActivePiece createNewPiece();
    void shiftActivePiece();
    std::size_t random_index(std::size_t lower,
                             std::size_t higher);
};
