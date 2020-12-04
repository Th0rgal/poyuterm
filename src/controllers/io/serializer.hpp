#pragma once
#include "models/gameData.hpp"
#include "models/grid.hpp"
#include <fstream>

class Serializer
{
public:
    Serializer(const char *fileName);
    void writeMode(GameData::GameMode mode);
    void writePiece(ActivePiece &piece);
    void writeGrid(Grid &grid);
    void writeScore(unsigned int score);
    void close();

private:
    char toLetter(const Grid::PuyoType type);
    std::ofstream file;
};