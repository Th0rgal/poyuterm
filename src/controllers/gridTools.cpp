#include "controllers/gridTools.hpp"
#include "domains/grid.hpp"

/**
 * 
 * 
 **/
std::vector<std::vector<Puyo>> runDetection(Grid &grid, std::vector<Coordinates> &starts)
{

    std::vector<std::vector<Puyo>> groups;
    for (Coordinates coordinates : starts)
    {
        Grid::PuyoType type = grid.content[coordinates.x][coordinates.y];
        std::vector<std::vector<Grid::PuyoType>> clonedContent = grid.content;
        std::vector<Puyo> group;
        extractGroup(group, clonedContent, coordinates);
        groups.push_back(group);
    }
    return groups;
}

void extractGroup(std::vector<Puyo> &group,
                  std::vector<std::vector<Grid::PuyoType>> &clonedContent,
                  Coordinates coordinates)
{
    Puyo puyo = Puyo(clonedContent[coordinates.x][coordinates.y],
                     coordinates.x,
                     coordinates.y);
    clonedContent[puyo.x][puyo.y] = Grid::none;
    group.push_back(puyo);

    if (puyo.x > 0 && clonedContent[puyo.x - 1][puyo.y] == puyo.type)
        extractGroup(group, clonedContent, Coordinates(puyo.x - 1, puyo.y));

    if (puyo.y > 0 && clonedContent[puyo.x][puyo.y - 1] == puyo.type)
        extractGroup(group, clonedContent, Coordinates(puyo.x, puyo.y - 1));

    if (puyo.x < 0 && clonedContent[puyo.x + 1][puyo.y] == puyo.type)
        extractGroup(group, clonedContent, Coordinates(puyo.x + 1, puyo.y));

    if (puyo.y < 0 && clonedContent[puyo.x][puyo.y + 1] == puyo.type)
        extractGroup(group, clonedContent, Coordinates(puyo.x, puyo.y + 1));
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