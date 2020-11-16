#pragma once
#include <vector>

using namespace std;

namespace grid
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
    vector<vector<PuyoType>> grid(6, vector<PuyoType>(12));
    bool trigger_gravity();
    void remove_adjectives();
}