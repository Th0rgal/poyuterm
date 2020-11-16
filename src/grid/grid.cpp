#include "grid.hpp"
#include <iostream>

using namespace grid;

/**
 * makes the falling puyo fall from a box
 * @return bool false if all puyo have fallen down
 **/
bool grid::trigger_gravity()
{
    vector<vector<PuyoType>> gridClone = grid;
    for (int x = 0; x < grid.size(); x++)
        for (int y = 0; y < grid[0].size() - 1; y++)
            if (gridClone[x][y] && !gridClone[x][y + 1])
            {
                grid[x][y + 1] = grid[x][y];
                grid[x][y] = PuyoType(none);
            }

    for (int x = 0; x < grid.size(); x++)
        for (int y = 0; y < grid[0].size() - 1; y++)
            if (grid[x][y] && !grid[x][y + 1])
                return false;
    return true;
}

/**
 * delete all combinations of linked puyos with a 
 * minimum size of 4
 **/
void grid::remove_adjectives()
{
    return;
}