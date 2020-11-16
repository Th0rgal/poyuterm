#include "grid.hpp"

using namespace grid;

/**
 * makes the falling puyo fall from a box
 * @return bool false if all puyo have fallen down
 **/
bool grid::trigger_gravity()
{
    for (int x = 0; x < grid.size(); x++)
        for (int y = 0; y < grid[0].size(); y++)
        {
            grid[4][6] = PuyoType(red);
        }
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