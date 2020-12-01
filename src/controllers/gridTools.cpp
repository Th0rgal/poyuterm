#include "controllers/gridTools.hpp"
#include "models/grid.hpp"
#include "models/gameData.hpp"
#include "models/puyo.hpp"
#include <bits/stdc++.h>
#include <ncurses.h>

/**
 * to teleport the active piece to the bottom if it is possible
 * 
 * @author Thomas Marchand
 **/
void teleportDown(Grid &grid, GameData &gameData, Display &display)
{
    // erase active Piece from displau
    gameData.activePiece.map([&](Puyo puyo) {
        (*display.game).setCell(puyo.x, puyo.y, Grid::none);
    });

    // snapshot grid content
    auto contentSnapshot = grid.content;

    // move activePiece to the ground
    bool finished;
    do
    {
        finished = true;
        gameData.activePiece.map([&](Puyo puyo) {
            if (puyo.y < grid.height() - 1 && grid.content[puyo.x][puyo.y - 1] && !grid.content[puyo.x][puyo.y])
            {
                finished = false;
                puyo.y += 1;
            }
        });

    } while (not finished);

    // write activePiece on the grid and remember coordinates
    std::unordered_set<Coordinates> starts;
    gameData.activePiece.map([&](Puyo puyo) {
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
        unsigned int score = 0;
        for (std::vector<Puyo> puyoList : detected)
        {
            for (Puyo puyo : puyoList)
                grid.content[puyo.x][puyo.y] = Grid::none;
            score = gameData.addScore(puyoList.size(), combosIndex, detected.size());
        }
        if (score != 0)
            (*display.game).displayScore(score);

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

    // reset activePiece
    gameData.activePiece.empty = true;

    // refresh display
    (*display.game).refreshDiff(contentSnapshot, grid);
}

/**
 * 
 * 
 **/
std::vector<std::vector<Puyo>> runDetection(Grid &grid, std::unordered_set<Coordinates> &starts)
{
    std::vector<std::vector<Puyo>> groups;
    std::vector<std::vector<Grid::PuyoType>> contentSample(grid.width(),
                                                           std::vector<Grid::PuyoType>(grid.height(), Grid::none));
    for (Coordinates coordinates : starts)
    {
        Grid::PuyoType type = grid.content[coordinates.x][coordinates.y];
        Grid clonedGrid = grid;
        std::vector<Puyo> group;
        extractGroup(group, clonedGrid, coordinates);
        bool duplicate = false;
        for (Puyo puyo : group)
        {
            if (contentSample[puyo.x][puyo.y])
            {
                duplicate = true;
                break;
            }
            else
            {
                contentSample[puyo.x][puyo.y] = puyo.type;
            }
        }
        if (!duplicate && group.size() >= 4)
            groups.push_back(group);
    }
    return groups;
}

void extractGroup(std::vector<Puyo> &group,
                  Grid &grid,
                  const Coordinates coordinates)
{
    Puyo puyo = Puyo(grid.content[coordinates.x][coordinates.y],
                     coordinates.x,
                     coordinates.y);
    grid.content[puyo.x][puyo.y] = Grid::none;
    group.push_back(puyo);

    if (puyo.x > 0 && grid.content[puyo.x - 1][puyo.y] == puyo.type)
        extractGroup(group, grid, Coordinates(puyo.x - 1, puyo.y));

    if (puyo.y > 0 && grid.content[puyo.x][puyo.y - 1] == puyo.type)
        extractGroup(group, grid, Coordinates(puyo.x, puyo.y - 1));

    if (puyo.x + 1 < grid.width() && grid.content[puyo.x + 1][puyo.y] == puyo.type)
        extractGroup(group, grid, Coordinates(puyo.x + 1, puyo.y));

    if (puyo.y + 1 < grid.height() && grid.content[puyo.x][puyo.y + 1] == puyo.type)
        extractGroup(group, grid, Coordinates(puyo.x, puyo.y + 1));
}

void runGravity(Grid &grid)
{
    // find starting points
    std::unordered_set<Coordinates> starts;
    for (std::size_t x = 0; x < grid.width(); x++)
        for (std::size_t y = grid.height() - 1; y >= 1; y--)
            if (grid.content[x][y - 1] && !grid.content[x][y])
            {
                grid.content[x][y] = grid.content[x][y - 1];
                grid.content[x][y - 1] = Grid::none;
                starts.emplace(x, y);
            }

    // run detections
    for (std::vector<Puyo> puyoList : runDetection(grid, starts))
        for (Puyo puyo : puyoList)
            grid.content[puyo.x][puyo.y] = Grid::none;
}

std::size_t std::hash<Coordinates>::operator()(const Coordinates &coordinates) const noexcept
{
    std::hash<std::size_t> size_t_hash;
    return size_t_hash(coordinates.x) ^ size_t_hash(coordinates.y);
}

Coordinates::Coordinates(std::size_t x, std::size_t y) : x(x), y(y)
{
}

bool Coordinates::operator==(const Coordinates &other) const
{
    return x == other.x && y == other.y;
}