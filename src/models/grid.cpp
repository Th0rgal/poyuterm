#include "models/grid.hpp"
#include <iostream>

/**
 * to intialize the grid with a 2d vector
 * @param vector<vector<PuyoType>> the initial grid content
 * 
 * @author Thomas Marchand
 **/
Grid::Grid(std::vector<std::vector<PuyoType>> initialGrid) : content(initialGrid)
{
}

/**
 * to get the grid width
 * @return std::size_t the length of the first line
 * 
 * @author Thomas Marchand
 **/
std::size_t Grid::width()
{
    return content.size();
}

/**
 * to get the grid height
 * @return std::size_t the length of the first column
 * 
 * @author Thomas Marchand
 **/
std::size_t Grid::height()
{
    return content.size() ? content[0].size() : 0;
}

void Grid::reset()
{
    content = std::vector(6, std::vector(12, PuyoType::none));
}