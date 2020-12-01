#pragma once
#include <functional>
#include "models/puyo.hpp"

class ActivePiece
{

public:
    ActivePiece();
    ActivePiece(Puyo center, Puyo side, unsigned int orientation);
    Puyo center;
    Puyo side;
    bool rotate(Grid &grid, unsigned int rotations = 1);
    bool shift(Grid &grid, int x, int y);
    void map(const std::function<void(Puyo &puyo)> &function);
    bool empty;

private:
    enum Orientation
    {
        west = 0,
        south = 1,
        east = 2,
        north = 3
    };
    Orientation _orientation;
};
