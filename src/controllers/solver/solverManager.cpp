#include "controllers/solver/solverManager.hpp"
#include "controllers/gridTools.hpp"
#include <bits/stdc++.h>

Snapshot::Snapshot(unsigned int score, Grid grid, std::size_t index) : _score(score), _grid(grid), _index(index)
{
}

void Snapshot::update(Snapshot snapshot)
{
    _score = snapshot._score;
    _grid = snapshot._grid;
    _index = snapshot._index;
}

Solver::Solver(Parser &parser)
{
    //todo : store all Puyos in pieces
}

void Solver::write(Serializer &serializer)
{
    //todo write a file from _pieces that could be simulated
}

void Solver::start()
{

    Grid baseGrid{std::vector<std::vector<Grid::PuyoType>>(6, std::vector<Grid::PuyoType>(12))};
}

void Solver::browse(Snapshot &output, Snapshot input, unsigned int calls)
{
    if (calls == 0 && (input._score > output._score || output._index < input._index))
    {
        output.update(input);
        return;
    }

    ActivePiece piece = _pieces[input._index];
    input._index++;
    for (std::size_t column = 0; column < input._grid.width() - 1; column++)
    {
        teleportDownVirtually(input._grid, piece);
        browse(output, input, calls - 1);
        piece.rotate(input._grid, 2);
        teleportDownVirtually(input._grid, piece);
        browse(output, input, calls - 1);
        piece.shift(input._grid, 1, 0);
    }
    piece.rotate(input._grid, 1);
    for (std::size_t column = 0; column < input._grid.width(); column++)
    {
        teleportDownVirtually(input._grid, piece);
        browse(output, input, calls - 1);
        piece.rotate(input._grid, 2);
        teleportDownVirtually(input._grid, piece);
        browse(output, input, calls - 1);
        piece.shift(input._grid, -1, 0);
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

unsigned int getScore(std::size_t groupSize, unsigned int combosIndex, unsigned int groupsNumber)
{
    return 10 * groupSize * (pow(4, combosIndex) + pow(3, groupsNumber));
}