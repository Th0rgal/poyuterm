#include <doctest/doctest.h>
#include "models/grid.hpp"
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

