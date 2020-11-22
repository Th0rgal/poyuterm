#include <doctest/doctest.h>
#include "domains/grid.hpp"
#include <iostream>

TEST_CASE("testing the constructor")
{
    std::vector<std::vector<Grid::PuyoType>> content = {
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

TEST_CASE("testing the width function")
{
    std::vector<std::vector<Grid::PuyoType>> content = {
        {Grid::red, Grid::none, Grid::none},
        {Grid::none, Grid::red, Grid::red}};
    Grid grid = Grid(content);
    CHECK(grid.width() == 2);

    content = {{Grid::red, Grid::none, Grid::none, Grid::pink}};
    grid = Grid(content);
    CHECK(grid.width() == 1);

    content = {};
    grid = Grid(content);
    CHECK(grid.width() == 0);
}

TEST_CASE("testing the height function")
{
    std::vector<std::vector<Grid::PuyoType>> content = {
        {Grid::red, Grid::none, Grid::none},
        {Grid::none, Grid::red, Grid::red}};
    Grid grid = Grid(content);
    CHECK(grid.height() == 3);

    content = {{Grid::red}, {Grid::pink}};
    grid = Grid(content);
    CHECK(grid.height() == 1);

    content = {};
    grid = Grid(content);
    CHECK(grid.height() == 0);
}

TEST_CASE("testing the triggerGravity function")
{

    std::vector<std::vector<Grid::PuyoType>> content = {
        {Grid::red, Grid::none, Grid::none},
        {Grid::none, Grid::red, Grid::none},
        {Grid::none, Grid::red, Grid::red}};

    std::vector<std::vector<Grid::PuyoType>> expectedOutput =
        {
            {Grid::none, Grid::red, Grid::none},
            {Grid::none, Grid::none, Grid::red},
            {Grid::none, Grid::red, Grid::red}};

    Grid grid = Grid(content);

    CHECK(grid.triggerGravity() == false);

    for (unsigned int x = 0; x < grid.content.size(); x++)
        for (unsigned int y = 0; y < grid.content.size(); y++)
            CHECK(grid.content[x][y] == expectedOutput[x][y]);

    CHECK(grid.triggerGravity() == true);
}
