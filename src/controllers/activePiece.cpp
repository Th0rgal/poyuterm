#include "controllers/activePiece.hpp"
#include <iostream>

ActivePiece::ActivePiece() : empty(true)
{
}

ActivePiece::ActivePiece(Puyo center, Puyo side, unsigned int orientation) : empty(false),
                                                                             center(center),
                                                                             side(side),
                                                                             _orientation(Orientation(orientation))
{
}

bool ActivePiece::rotate(Grid &grid)
{

    if (_orientation == west && side.x + 1 < grid.width() && side.y + 1 < grid.height() && not grid.content[side.x + 1][side.y + 1])
    {

        side.x += 1;
        side.y += 1;
    }
    else if (_orientation == south && side.x + 1 < grid.width() && side.y > 0 && not grid.content[side.x + 1][side.y - 1])
    {
        side.x += 1;
        side.y -= 1;
    }
    else if (_orientation == east && center.y + 1 < grid.height() && side.y > 0 && not grid.content[center.x][center.y + 1] && not grid.content[side.x][side.y - 1])
    {
        center.y += 1;
        side.y -= 1;
    }
    else if (_orientation == north && center.x + 1 < grid.width() && center.y > 0 && not grid.content[center.x + 1][center.y - 1])
    {
        center.x += 1;
        center.y -= 1;
    }
    else
        return false;

    _orientation = Orientation((_orientation + 1) % 4);
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