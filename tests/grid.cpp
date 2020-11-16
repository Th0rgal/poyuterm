#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include "domains/grid.hpp"
#include <iostream>

TEST_CASE("testing the constructor")
{
    vector<vector<Grid::PuyoType>> content =
        {
            {Grid::red, Grid::none, Grid::none},
            {Grid::none, Grid::red, Grid::red},
            {Grid::none, Grid::none, Grid::red}};

    Grid grid = Grid(content);
    CHECK(grid.content == content);

    content =
        {
            {Grid::none, Grid::blue},
            {Grid::red, Grid::yellow},
            {Grid::green, Grid::none}};

    grid = Grid(content);
    CHECK(grid.content == content);
}

TEST_CASE("testing the triggerGravity function")
{

    vector<vector<Grid::PuyoType>> content = {
        {Grid::red, Grid::none, Grid::none},
        {Grid::none, Grid::red, Grid::red},
        {Grid::none, Grid::none, Grid::red}};

    vector<vector<Grid::PuyoType>> expectedOutput =
        {
            {Grid::none, Grid::none, Grid::none},
            {Grid::red, Grid::none, Grid::red},
            {Grid::none, Grid::red, Grid::red}};

    Grid grid = Grid(content);

    CHECK(grid.triggerGravity() == false);

    for (int x = 0; x < grid.content.size(); x++)
        for (int y = 0; y < grid.content.size(); y++)
            CHECK(grid.content[x][y] == expectedOutput[x][y]);

    CHECK(grid.triggerGravity() == true);
}