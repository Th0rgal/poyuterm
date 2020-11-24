#pragma once
#include <vector>
#include "domains/grid.hpp"

struct Puyo
{
    Grid::PuyoType type;
    std::size_t x;
    std::size_t y;
    Puyo();
    Puyo(Grid::PuyoType type, std::size_t x, std::size_t y);
    void move(std::size_t x, std::size_t y);
    bool operator==(const Puyo &other) const;
};

struct GameData
{
    GameData();
    std::vector<Puyo> activePiece;
    long delaySinceGravity;
};

bool shift(std::vector<Puyo> &activePiece, Grid constraint, int x, int y);