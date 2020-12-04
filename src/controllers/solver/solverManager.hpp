#pragma once

#include "controllers/activePiece.hpp"
#include "controllers/io/parser.hpp"
#include <vector>

class Solver
{
public:
    Solver(Parser &parser);
    void start();
    unsigned int teleportDownVirtually(Grid &grid, ActivePiece &activePiece);
    unsigned int computeEfficiencyIndex(Grid &grid);
    unsigned int computeHighestColumnSize(Grid &grid);

private:
    Parser &_parser;
    void compute(Grid grid, ActivePiece piece, Grid &clone, unsigned int &scoreBonus, bool &scoreChanged, unsigned int &efficiencyIndex,
                 bool &efficiencyChanged, unsigned int &highestColumnSize);
};

unsigned int getScore(std::size_t groupSize, unsigned int combosIndex, unsigned int groupsNumber);