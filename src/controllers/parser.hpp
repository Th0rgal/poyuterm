#pragma once
#include "models/gameData.hpp"
#include "models/grid.hpp"
#include <vector>
#include <fstream>

class Parser
{
public:
    Parser(char *fileName);
    GameData::GameMode gameMode;
    bool next(Grid &constraint);
    std::vector<Puyo> activePiece;

private:
    std::ifstream file;
};