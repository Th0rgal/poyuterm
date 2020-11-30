#pragma once
#include "models/gameData.hpp"
#include "models/grid.hpp"
#include <vector>
#include <fstream>
#include "controllers/activePiece.hpp"

class Parser
{
public:
    Parser();
    Parser(char *fileName);
    char *fileName;
    bool next(Grid &constraint);

    bool enabled;
    GameData::GameMode gameMode;
    ActivePiece activePiece;

private:
    std::ifstream file;
    Grid::PuyoType toPuyoType(char letter);
};