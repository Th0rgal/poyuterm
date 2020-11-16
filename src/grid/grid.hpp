#pragma once
#include <vector>

using namespace std;

namespace grid
{
    enum PuyoType
    {
        red,
        green,
        yellow,
        blue,
        pink
    };
    vector<vector<PuyoType>> grid(6, vector<PuyoType>(12));
    bool trigger_gravity();
    void remove_adjectives();
}