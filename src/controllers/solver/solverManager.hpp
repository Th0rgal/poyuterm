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
    unsigned int computeEfficiencyIndex(Grid &grid, unsigned int tempHighestColumnSize);
    unsigned int computeHighestColumnSize(Grid &grid);

private:
    Parser &_parser;
    unsigned int _scoreBonus;
    bool _scoreChanged;
    unsigned int _efficiencyIndex;
    bool _efficiencyChanged;
    unsigned int _highestColumnSize;
    ActivePiece _piece;
    Grid _gridClone{std::vector<std::vector<Grid::PuyoType>>(6, std::vector<Grid::PuyoType>(12))};
    void compute(Grid grid, ActivePiece piece);
};

unsigned int getScore(std::size_t groupSize, unsigned int combosIndex, unsigned int groupsNumber);