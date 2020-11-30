#pragma once
#include "models/gameData.hpp"
#include "models/grid.hpp"
#include <vector>
#include <fstream>

class Parser
{
public:
    Parser();
    Parser(char *fileName);
    bool next(Grid &constraint);

    bool enabled;
    GameData::GameMode gameMode;
    std::vector<Puyo> activePiece;

private:
    std::ifstream file;
};