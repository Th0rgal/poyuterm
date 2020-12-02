#include "models/grid.hpp"
#include <iostream>

/**
 * to intialize the grid with a 2d vector
 * @param vector<vector<PuyoType>> the initial grid content
 * 
 * @author Thomas Marchand
 * @confidence 5
 **/
Grid::Grid(std::vector<std::vector<PuyoType>> initialGrid) : content(initialGrid)
{
}

/**
 * to get the grid width
 * @return std::size_t the length of the first line
 * 
 * @author Thomas Marchand
 * @confidence 5
 **/
std::size_t Grid::width()
{
    return content.size();
}

/**
 * to get the grid height
 * @return std::size_t the length of a column (0 if empty)
 * 
 * @author Thomas Marchand
 * @confidence 5
 **/
std::size_t Grid::height()
{
    return content.size() ? content[0].size() : 0;
}

void Grid::reset()
{
    content = std::vector(6, std::vector(12, PuyoType::none));
}