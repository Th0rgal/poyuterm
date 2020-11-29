#pragma once

#include <vector>
#include "models/grid.hpp"
#include "models/gameData.hpp"
#include <bits/stdc++.h>

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
bool shift(std::vector<Puyo> &activePiece, Grid constraint, int x, int y);
bool rotate(std::vector<Puyo> &activePiece, Grid constraint);