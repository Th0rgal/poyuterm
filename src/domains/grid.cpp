#include "domains/grid.hpp"
#include <iostream>

/**
 * to intialize the grid with a 2d vector
 * @param vector<vector<PuyoType>> the initial grid content
 **/
Grid::Grid(std::vector<std::vector<PuyoType>> initialGrid) : content(initialGrid)
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
 * to delete all combinations of linked puyos with 
 * a minimum size of 4
 **/
void Grid::removeAdjectives()
{
    return;
}