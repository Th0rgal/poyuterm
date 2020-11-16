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
    vector<vector<PuyoType>> content;
    Grid(vector<vector<PuyoType>> initialGrid);
    void setContent(vector<vector<PuyoType>> newGrid);
    bool triggerGravity();
    void removeAdjectives();
};