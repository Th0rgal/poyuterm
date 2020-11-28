#pragma once

#include <vector>
#include "models/grid.hpp"
#include "models/gameData.hpp"

struct Coordinates
{
    std::size_t x;
    std::size_t y;
    Coordinates(std::size_t x, std::size_t y);
    void add(std::size_t x, std::size_t y);

    Coordinates operator+=(const Coordinates &coordinate);
    Coordinates operator+(Coordinates coordinate);
};

std::vector<std::vector<Puyo>> runDetection(const Grid &grid, std::vector<Coordinates> &starts);

void extractGroup(std::vector<Puyo> &group,
                  Grid &clonedGrid,
                  const Coordinates coordinates);

bool runGravity(Grid &grid);
bool shift(std::vector<Puyo> &activePiece, Grid constraint, int x, int y);
bool rotate(std::vector<Puyo> &activePiece, Grid constraint);