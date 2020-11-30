#include "controllers/activePiece.hpp"

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

void ActivePiece::map(const std::function<void(Puyo)> &function)
{
    function(center);
    function(side);
}