#pragma once
#include <vector>

using namespace std;

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
    int width();
    int height();
    Grid(vector<vector<PuyoType>> initialGrid);
    bool triggerGravity();
    void removeAdjectives();
    vector<vector<PuyoType>> content;
};