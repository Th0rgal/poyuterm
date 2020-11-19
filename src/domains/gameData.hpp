#pragma once
#include <utility>
#include <vector>

struct GameData
{
    GameData();
    std::vector<std::pair<std::size_t, std::size_t>> activePiece;
    long delaySinceGravity;
};