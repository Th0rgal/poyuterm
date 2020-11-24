#pragma once
#include <vector>

struct Grid
{
    enum PuyoType
    {
        none = 0,
        red = 1,
        green = 2,
        yellow = 3,
        blue = 4,
        pink = 5
    };
    std::size_t width();
    std::size_t height();
    Grid(std::vector<std::vector<PuyoType>> initialGrid);
    void removeAdjectives();
    std::vector<std::vector<PuyoType>> content;
};