#include "controllers/gridTools.hpp"
#include "domains/grid.hpp"

/**
 * 
 * 
 **/
std::vector<std::vector<Puyo>> runDetection(const Grid &grid, std::vector<Coordinates> &starts)
{
    std::vector<std::vector<Puyo>> groups;
    for (Coordinates coordinates : starts)
    {
        Grid::PuyoType type = grid.content[coordinates.x][coordinates.y];
        Grid clonedGrid = grid;
        std::vector<Puyo> group;
        extractGroup(group, clonedGrid, coordinates);
        if (group.size() >= 4)
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

Coordinates::Coordinates(std::size_t x, std::size_t y) : x(x), y(y)
{
}

void Coordinates::add(std::size_t xAdd, std::size_t yAdd)
{
    x += xAdd;
    y += yAdd;
}

Coordinates Coordinates::operator+=(const Coordinates &coordinate)
{
    add(coordinate.x, coordinate.y);
    return *this;
}

Coordinates Coordinates::operator+(Coordinates coordinate)
{
    return coordinate += *this;
}