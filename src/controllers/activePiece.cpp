#include "controllers/activePiece.hpp"

ActivePiece::ActivePiece() : empty(true)
{
}

ActivePiece::ActivePiece(Puyo center, Puyo side, unsigned int orientation) : empty(false),
                                                                             center(center),
                                                                             side(side),
                                                                             _orientation(Orientation(orientation))
{
}

bool ActivePiece::rotate(Grid &grid, unsigned int rotations)
{
    int center_x = center.x;
    int center_y = center.y;
    int side_x = side.x;
    int side_y = side.y;
    Orientation clonedOrientation = _orientation;

    for (std::size_t i = 0; i < rotations; i++)
    {
        switch (clonedOrientation)
        {
        case west:
            center_x -= 1;
            side_y += 1;
            break;
        case south:
            side_x += 1;
            side_y -= 1;
            break;
        case east:
            center_y += 1;
            side_x -= 1;
            break;
        case north:
            center_x += 1;
            center_y -= 1;
            break;
        }
        clonedOrientation = Orientation((clonedOrientation + 1) % 4);
    }

    bool centerCorrect = center_x >= 0 && center_x < grid.width() && center_y >= 0 && center_y < grid.height();
    bool sideCorrect = side_x >= 0 && side_x < grid.width() && side_y >= 0 && side_y < grid.height();
    if (centerCorrect && sideCorrect && !grid.content[center_x][center_y] && !grid.content[side_x][side_y])
    {
        center.x = center_x;
        center.y = center_y;
        side.x = side_x;
        side.y = side_y;
        _orientation = clonedOrientation;
        return true;
    }

    return false;
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