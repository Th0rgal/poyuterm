#include <doctest/doctest.h>
#include "models/grid.hpp"
#include "controllers/gridTools.hpp"
#include <bits/stdc++.h>

TEST_CASE("testing shift")
{
    std::vector<std::vector<Grid::PuyoType>> content(6, std::vector<Grid::PuyoType>(12));

    ActivePiece activePiece(
        Puyo(Grid::red, 1, 0),
        Puyo(Grid::green, 2, 0), 0);

    Grid grid = Grid(content);
    GameData gameData = GameData();
    gameData.activePiece = activePiece;
    bool moved = activePiece.shift(grid, 1, 0);

    CHECK(moved == true);
    CHECK(activePiece.center == Puyo(Grid::red, 2, 0));
    CHECK(activePiece.side == Puyo(Grid::green, 3, 0));

    moved = activePiece.shift(grid, 0, -1);
    CHECK(moved == false);
    CHECK(activePiece.center == Puyo(Grid::red, 2, 0));
    CHECK(activePiece.side == Puyo(Grid::green, 3, 0));

    moved = activePiece.shift(grid, -1, 0);
    CHECK(moved == true);
    CHECK(activePiece.center == Puyo(Grid::red, 1, 0));
    CHECK(activePiece.side == Puyo(Grid::green, 2, 0));
}

TEST_CASE("testing detection")
{
    std::vector<std::vector<Grid::PuyoType>> content(6, std::vector<Grid::PuyoType>(12));
    content[1][0] = Grid::red;
    content[1][1] = Grid::red;
    content[2][0] = Grid::red;
    content[3][0] = Grid::red;

    Grid grid = Grid(content);
    std::unordered_set<Coordinates> starts{Coordinates(2, 0)};
    std::vector<std::vector<Puyo>> detected = runDetection(grid, starts);

    // to ensure grid.content has not been altered
    CHECK(detected.size() == 1);
    for (std::size_t x; x < grid.width(); x++)
        for (std::size_t y; y < grid.height(); y++)
            CHECK(grid.content[x][y] == content[x][y]);
}

TEST_CASE("testing gravity")
{
    std::vector<std::vector<Grid::PuyoType>> content(6, std::vector<Grid::PuyoType>(12));
    content[1][0] = Grid::blue;
    content[1][1] = Grid::yellow;
    content[3][10] = Grid::pink;
    content[3][11] = Grid::red;

    std::vector<std::vector<Grid::PuyoType>> expectedContent(6, std::vector<Grid::PuyoType>(12));
    expectedContent[1][1] = Grid::blue;
    expectedContent[1][2] = Grid::yellow;
    expectedContent[3][10] = Grid::pink;
    expectedContent[3][11] = Grid::red;

    Grid grid = Grid(content);
    runGravity(grid);
    for (std::size_t x = 0; x < grid.width(); x++)
        for (std::size_t y = 0; y < grid.width(); y++)
            CHECK(grid.content[x][y] == expectedContent[x][y]);

    expectedContent = std::vector<std::vector<Grid::PuyoType>>(6, std::vector<Grid::PuyoType>(12));
    expectedContent[1][10] = Grid::blue;
    expectedContent[1][11] = Grid::yellow;
    expectedContent[3][10] = Grid::pink;
    expectedContent[3][11] = Grid::red;

    for (std::size_t i = 0; i < 9; i++)
        runGravity(grid);

    for (std::size_t x = 0; x < grid.width(); x++)
        for (std::size_t y = 0; y < grid.width(); y++)
            CHECK(grid.content[x][y] == expectedContent[x][y]);
}
