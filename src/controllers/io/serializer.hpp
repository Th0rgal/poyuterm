#pragma once
#include "models/gameData.hpp"
#include "models/grid.hpp"
#include <fstream>

class Serializer
{
public:
    Serializer(const char *fileName);
    void writeGrid(Grid &grid);
    void writeScore(unsigned int score);

private:
    std::ofstream file;
};