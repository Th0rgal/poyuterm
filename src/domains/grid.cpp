#include "domains/grid.hpp"
#include <iostream>

/**
 * to intialize the grid with a 2d vector
 * @param vector<vector<PuyoType>> the initial grid content
 **/
Grid::Grid(vector<vector<PuyoType>> initialGrid) : content(initialGrid)
{
}

/**
 * to get the grid width
 * @return int the length of the first line
 **/
std::size_t Grid::width()
{
    return content.size();
}

/**
 * to get the grid height
 * @return int the length of the first column
 **/
std::size_t Grid::height()
{
    return content.size() ? content[0].size() : 0;
}

/**
 * to make the falling puyo fall from a box
 * @return bool false if all puyo have fallen down
 **/
bool Grid::triggerGravity()
{
    vector<vector<PuyoType>> clone = content;
    for (std::size_t x = 0; x < clone.size(); x++)
        for (std::size_t y = 0; y < clone[0].size() - 1u; y++)
            if (clone[x][y] && !clone[x][y + 1])
            {
                content[x][y + 1] = clone[x][y];
                content[x][y] = none;
            }

    for (std::size_t x = 0; x < content.size(); x++)
        for (std::size_t y = 0; y < content[0].size() - 1u; y++)
            if (content[x][y] && !content[x][y + 1])
                return false;
    return true;
}

/**
 * to delete all combinations of linked puyos with 
 * a minimum size of 4
 **/
void Grid::removeAdjectives()
{
    return;
}