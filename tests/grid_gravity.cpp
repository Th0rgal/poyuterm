#include "../src/grid/grid.hpp"
#include "../src/grid/grid.cpp"
#include <iostream>

int main()
{
    grid::grid = {{red, red, red},
                  {none, none, none},
                  {none, none, none}};
    vector<vector<PuyoType>> output = {{none, none, none},
                                       {red, red, red},
                                       {none, none, none}};

    
    grid::trigger_gravity();

    for (int x = 0; x < grid::grid.size(); x++)
        for (int y = 0; y < grid::grid.size(); y++)
            if (grid::grid[x][y] != output[x][y]) {
                return 1;
            }

    return 0;
}