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
    void add(std::size_t x, std::size_t y);

    Puyo operator+=(const Puyo &coordinate);
    Puyo operator+(Puyo coordinate);
};

struct GameData
{
    GameData();
    std::vector<Puyo> activePiece;
    long delaySinceGravity;
};