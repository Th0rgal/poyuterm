#include "controllers/solver/solverManager.hpp"
#include "controllers/io/serializer.hpp"
#include "controllers/gridTools.hpp"
#include <bits/stdc++.h>
#include <algorithm>
#include <iostream>

Solver::Solver(Parser &parser) : _parser(parser)
{
}

void Solver::start()
{
    Serializer serializer("sortie.txt");
    serializer.writeMode(GameData::simulation);
    Grid grid{std::vector<std::vector<Grid::PuyoType>>(6, std::vector<Grid::PuyoType>(12))};
    unsigned int score = 0;
    while (_parser.next(0))
    {
        _changed = false;
        _scoreBonus = 0;
        _scoreChanged = false;
        _efficiencyIndex = 0;
        _efficiencyChanged = false;
        _highestColumnSize = grid.height() + 1;
        _gridClone = grid;
        ActivePiece piece = _parser.activePiece;
        for (std::size_t column = 0; column < grid.width() - 1; column++)
        {
            compute(grid, piece);
            piece.rotate(grid, 2);
            compute(grid, piece);
            piece.shiftNoCheck(grid, 1, 0);
        }
        piece.rotate(grid, 1);
        for (std::size_t column = 0; column < grid.width(); column++)
        {
            compute(grid, piece);
            piece.rotate(grid, 2);
            compute(grid, piece);
            piece.shiftNoCheck(grid, -1, 0);
        }

        if (!_changed)
            break;

        grid = _gridClone;
        serializer.writePiece(_piece);
    }
    _parser.close();
    serializer.close();
}

void Solver::compute(Grid grid, ActivePiece piece)
{
    bool changed = true;
    piece.map([&](Puyo &puyo) {
        if (grid.content[puyo.x][puyo.y])
            changed = false;
    });
    if (!changed)
        return;
    _changed = true;

    unsigned int tempScore = teleportDownVirtually(grid, piece);
    if (tempScore > _scoreBonus && tempScore > 280)
    {
        _scoreChanged = true;
        _gridClone = grid;
        _scoreBonus = tempScore;
        _piece = piece;
    }
    if (_scoreChanged)
        return;

    unsigned int tempHighestColumnSize = computeHighestColumnSize(grid);
    unsigned int tempEfficiencyIndex = computeEfficiencyIndex(grid, tempHighestColumnSize);
    if (tempEfficiencyIndex > _efficiencyIndex)
    {
        _efficiencyChanged = true;
        _gridClone = grid;
        _efficiencyIndex = tempEfficiencyIndex;
        _piece = piece;
    }
    if (_efficiencyChanged)
        return;

    if (tempHighestColumnSize < _highestColumnSize)
    {
        _gridClone = grid;
        _highestColumnSize = tempHighestColumnSize;
        _piece = piece;
    }
}

unsigned int Solver::teleportDownVirtually(Grid &grid, ActivePiece &activePiece)
{
    unsigned int scoreBonus = 0;

    // snapshot grid content
    auto contentSnapshot = grid.content;

    // move activePiece to the ground
    bool finished;
    do
    {
        finished = true;
        activePiece.map([&](Puyo puyo) {
            if (puyo.y < grid.height() - 1 && grid.content[puyo.x][puyo.y - 1] && !grid.content[puyo.x][puyo.y])
            {
                finished = false;
                puyo.y += 1;
            }
        });

    } while (not finished);

    // write activePiece on the grid and remember coordinates
    std::unordered_set<Coordinates> starts;
    activePiece.map([&](Puyo puyo) {
        grid.content[puyo.x][puyo.y] = puyo.type;
        starts.emplace(puyo.x, puyo.y);
    });

    unsigned int combosIndex = 0;
    while (!starts.empty())
    {
        // detect 4+ groups and destroy them
        auto detected = runDetection(grid, starts);
        if (detected.size() > 0)
            combosIndex++;
        for (std::vector<Puyo> puyoList : detected)
        {
            for (Puyo puyo : puyoList)
                grid.content[puyo.x][puyo.y] = Grid::none;
            scoreBonus = getScore(puyoList.size(), combosIndex, detected.size());
        }

        // move everything to the ground
        bool finished;
        starts = {};
        do
        {
            finished = true;
            for (std::size_t x = 0; x < grid.width(); x++)
                for (std::size_t y = grid.height() - 1; y >= 1; y--)
                    if (grid.content[x][y - 1] && !grid.content[x][y])
                    {
                        grid.content[x][y] = grid.content[x][y - 1];
                        grid.content[x][y - 1] = Grid::none;
                        starts.erase(Coordinates(x, y - 1));
                        starts.emplace(x, y);
                        finished = false;
                    }
        } while (not finished);
    }
    return scoreBonus;
}

unsigned int Solver::computeEfficiencyIndex(Grid &grid, unsigned int tempHighestColumnSize)
{
    std::unordered_set<Coordinates> starts;
    for (std::size_t x = 0; x < grid.width(); x++)
        for (std::size_t y = 1; y < grid.height(); y++)
        {
            if (!grid.content[x][y - 1] && grid.content[x][y])
                starts.emplace(x, y);
            else if (x > 0 && !grid.content[x - 1][y] && grid.content[x][y])
                starts.emplace(x, y);
            else if (x + 1 < grid.width() - 1 && !grid.content[x + 1][y] && grid.content[x][y])
                starts.emplace(x, y);
        }

    unsigned int counter = 0;
    if (tempHighestColumnSize < grid.height() - 3)
        for (auto group : runDetection(grid, starts, 2))
            counter += group.size();

    return counter;
}

unsigned int Solver::computeHighestColumnSize(Grid &grid)
{
    unsigned int highestColumnSize = 0;
    for (auto column : grid.content)
    {
        unsigned int columnSize = 0;
        for (Grid::PuyoType type : column)
            if (type != Grid::none)
                columnSize += 1;
        if (columnSize > highestColumnSize)
            highestColumnSize = columnSize;
    }
    return highestColumnSize;
}

unsigned int getScore(std::size_t groupSize, unsigned int combosIndex, unsigned int groupsNumber)
{
    return 10 * groupSize * (pow(4, combosIndex) + pow(3, groupsNumber));
}