#pragma once
#include <utility>
#include <vector>

struct GameData
{
    GameData();
    std::vector<std::pair<int, int>> activePiece;
    double delaySinceGravity;
};