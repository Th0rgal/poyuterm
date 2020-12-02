#pragma once

#include <vector>
#include <bits/stdc++.h>
#include "models/grid.hpp"
#include "models/gameData.hpp"
#include "models/puyo.hpp"
#include "views/display.hpp"

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

void teleportDown(Grid &grid, GameData &gameData, Display &display);
std::vector<std::vector<Puyo>> runDetection(Grid &grid, std::unordered_set<Coordinates> &starts);

void extractGroup(std::vector<Puyo> &group,
                  Grid &clonedGrid,
                  const Coordinates coordinates);

void runGravity(Grid &grid);
void runPuyoGravity(Grid &grid, GameData &gameData);