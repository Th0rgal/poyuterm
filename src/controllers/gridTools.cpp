#include "controllers/gridTools.hpp"
#include "models/grid.hpp"
#include "models/gameData.hpp"
#include <bits/stdc++.h>
#include <ncurses.h>

/**
 * to teleport the active piece to the bottom if it is possible
 * 
 * @author Thomas Marchand
 **/
void teleportDown(Grid &grid, GameData &gameData, Display &display)
{
    int score = 0;
    // erase active Piece from displau
    for (Puyo puyo : gameData.activePiece)
        (*display.game).setCell(puyo.x, puyo.y, Grid::none);
    // snapshot grid content
    auto contentSnapshot = grid.content;

    // move activePiece to the ground
    bool finished;
    do
    {
        finished = true;
        for (Puyo &puyo : gameData.activePiece)
            if (puyo.y < grid.height() - 1 && grid.content[puyo.x][puyo.y - 1] && !grid.content[puyo.x][puyo.y])
            {
                finished = false;
                puyo.y += 1;
            }
    } while (not finished);

    // write activePiece on the grid and remember coordinates
    std::unordered_set<Coordinates> starts;
    for (Puyo puyo : gameData.activePiece)
    {
        grid.content[puyo.x][puyo.y] = puyo.type;
        starts.emplace(puyo.x, puyo.y);
    }

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
            score = gameData.addScore(puyoList.size(), combosIndex, detected.size());
        }
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
    gameData.activePiece = {};

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

/**
 * to shift the falling piece in gameData and on the grid
 * @param std::vector<Puyo> &activePiece the falling piece to shift
 * @param Grid::Grid constraint the grid to compare to
 * @param int x, -1 <= x <= 1, the shift on the x axis
 * @param int y, -1 <= y <= 1, the shift on the y axis
 * @return bool true if the piece has been shifted
 * 
 * @author Thomas Marchand
 **/
bool shift(std::vector<Puyo> &activePiece, Grid constraint, int x, int y)
{
    const size_t size = activePiece.size();
    std::vector<Puyo> updatedPiece(size);

    for (size_t i = 0; i < size; i++)
    {
        Puyo puyo = activePiece[i];

        // avoid impossible x
        if (static_cast<int>(puyo.x) + x < 0 ||
            static_cast<int>(puyo.x) + x >= static_cast<int>(constraint.width()))
            return false;

        // avoid impossible y
        if (static_cast<int>(puyo.y) + y < 0 ||
            static_cast<int>(puyo.y) + y >= static_cast<int>(constraint.height()))
            return false;

        puyo.move(x, y);

        // avoid overwriting
        if (constraint.content[puyo.x][puyo.y])
            return false;

        updatedPiece[i] = puyo;
    }

    for (std::size_t i = 0; i < updatedPiece.size(); i++)
        activePiece[i] = updatedPiece[i];

    return true;
}

bool rotate(std::vector<Puyo> &activePiece, Grid constraint)
{
    const size_t size = activePiece.size();
    std::vector<Puyo> updatedPiece(size);
    int sens = (activePiece[0].x - activePiece[1].x) + 2 * (activePiece[0].y - activePiece[1].y);
    int leftColision = activePiece[size - 1].x - (size - 1);
    int xTranslation = 0;
    bool xColoneColision = false;
    int xColision = 0;
    int yTranslation = 0;

    for (size_t i = 0; i < size; i++)
    {
        Puyo puyo = activePiece[i];

        if (puyo.x == 5 && (sens == 2 || sens == -2))
        {
            xColision = -1;
        }

        switch (sens)
        {
        case -1:
            xTranslation = -i + xColision;
            yTranslation = size - 1 - i;
            break;

        case 2:
            xTranslation = size - i - 1 + xColision;
            yTranslation = i - 1;
            break;

        case 1:
            xTranslation = i - 1 + xColision;
            yTranslation = size - 2 + i;
            break;

        case -2:
            xTranslation = i + 2 - size + xColision;
            yTranslation = -i;
            break;
        }
        if (puyo.y + yTranslation > 11 ||
            puyo.x + xTranslation > 5)
            return false;
        if (constraint.content[puyo.x + xTranslation][puyo.y + yTranslation] != Grid::none)
        {
            if (sens == -1 || sens == 1)
            {
                for (int iColsion = 0; iColsion < i; iColsion++)
                {
                    Puyo puyoX = updatedPiece[iColsion];
                    puyoX.move(1, 0);
                    updatedPiece[iColsion] = puyoX;
                }
                xTranslation++;
                xColision = 1;
            }
            else
            {
                return false;
            }
        }

        puyo.move(xTranslation, yTranslation);
        updatedPiece[i] = puyo;
    }

    for (std::size_t i = 0; i < updatedPiece.size(); i++)
        activePiece[i] = updatedPiece[i];
    return true;
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