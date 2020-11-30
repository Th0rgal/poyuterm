#include "controllers/activePiece.hpp"
#include <iostream>

ActivePiece::ActivePiece() : empty(true)
{
}

ActivePiece::ActivePiece(Puyo center, Puyo side, unsigned int orientation) : center(center),
                                                                             side(side),
                                                                             orientation(Orientation(orientation))
{
}

bool ActivePiece::rotate(Grid &grid)
{
    switch (orientation)
    {
    case west:
        if (side.x + 1 >= grid.width() || side.y + 1 >= grid.height() || grid.content[side.x + 1][side.y + 1])
            return false;
        side.x += 1;
        side.y += 1;
        break;
    case south:
        if (side.x + 1 >= grid.width() || side.y == 0 || grid.content[side.x + 1][side.y - 1])
            return false;
        side.x += 1;
        side.y -= 1;
        break;
    case east:
        if (center.y + 1 >= grid.height() || side.y == 0 || grid.content[center.x][center.y + 1] || grid.content[side.x][side.y - 1])
            return false;
        center.y += 1;
        side.y -= 1;
        break;
    case north:
        if (center.x + 1 >= grid.width() || center.y == 0 || grid.content[center.x + 1][center.y - 1])
            return false;
        center.x += 1;
        center.y -= 1;
        break;
    }
    orientation = Orientation((orientation + 1) % 4);
    return true;
}

bool ActivePiece::shift(Grid &grid, int x, int y)
{

    std::vector<Puyo> piece = {center, side};
    for (Puyo &puyo : piece)
    {
        // avoid impossible x
        if (static_cast<int>(puyo.x) + x < 0 ||
            static_cast<int>(puyo.x) + x >= static_cast<int>(grid.width()))
            return false;

        // avoid impossible y
        if (static_cast<int>(puyo.y) + y < 0 ||
            static_cast<int>(puyo.y) + y >= static_cast<int>(grid.height()))
            return false;

        puyo.move(x, y);

        // avoid overwriting
        if (grid.content[puyo.x][puyo.y])
            return false;
    }
    center = piece[0];
    side = piece[1];
    return true;
}

void ActivePiece::map(const std::function<void(Puyo &puyo)> &function)
{
    function(center);
    function(side);
}

void ActivePiece::setEmpty()
{
    empty = true;
}

bool ActivePiece::isEmpty()
{
    return empty;
}