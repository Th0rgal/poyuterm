#pragma once

#include <vector>
#include <bits/stdc++.h>
#include "models/grid.hpp"
#include "models/gameData.hpp"
#include "models/puyo.hpp"

struct Coordinates
{
    std::size_t x;
    std::size_t y;
    Coordinates(std::size_t x, std::size_t y);
    bool operator==(const Coordinates &other) const;
};

template <>
struct std::hash<Coordinates>
{
    std::size_t operator()(const Coordinates &coordinates) const noexcept;
};

std::vector<std::vector<Puyo>> runDetection(Grid &grid,
                                            std::unordered_set<Coordinates> &starts,
                                            const unsigned int triggerSize = 4);

void extractGroup(std::vector<Puyo> &group,
                  Grid &clonedGrid,
                  const Coordinates coordinates);

void runGravity(Grid &grid);
void runPuyoGravity(Grid &grid, GameData &gameData);