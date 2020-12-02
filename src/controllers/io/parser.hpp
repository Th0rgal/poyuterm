#pragma once

#include <fstream>
#include "models/grid.hpp"
#include "models/gameData.hpp"
#include "controllers/activePiece.hpp"

class Parser
{
public:
    Parser();
    Parser(char *fileName);
    char *fileName;
    bool next(Grid &constraint);
    bool next(std::size_t column);

    bool enabled;
    GameData::GameMode gameMode;
    ActivePiece activePiece;

private:
    std::ifstream file;
    Grid::PuyoType toPuyoType(char letter);
};