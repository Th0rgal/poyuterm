#pragma once

#include "models/grid.hpp"

struct Puyo
{
    Grid::PuyoType type;
    std::size_t x;
    std::size_t y;
    Puyo();
    Puyo(Grid::PuyoType type, std::size_t x, std::size_t y);
    void move(int x, int y);
    bool operator==(const Puyo &other) const;
};