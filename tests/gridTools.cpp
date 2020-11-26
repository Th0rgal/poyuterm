#include <doctest/doctest.h>
#include "domains/grid.hpp"
#include "controllers/gridTools.hpp"

TEST_CASE("testing shift")
{
    std::vector<std::vector<Grid::PuyoType>> content(6, std::vector<Grid::PuyoType>(12));

    std::vector<Puyo> activePiece = {
        Puyo(Grid::red, 1, 0),
        Puyo(Grid::green, 2, 0)};

    Grid grid = Grid(content);
    GameData gameData = GameData();
    gameData.activePiece = activePiece;
    bool moved = shift(activePiece, grid, 1, 0);

    CHECK(moved == true);
    CHECK(activePiece.size() == 2);
    CHECK(activePiece[0] == Puyo(Grid::red, 2, 0));
    CHECK(activePiece[1] == Puyo(Grid::green, 3, 0));

    moved = shift(activePiece, grid, 0, -1);
    CHECK(moved == false);
    CHECK(activePiece.size() == 2);
    CHECK(activePiece[0] == Puyo(Grid::red, 2, 0));
    CHECK(activePiece[1] == Puyo(Grid::green, 3, 0));

    moved = shift(activePiece, grid, -1, 0);
    CHECK(moved == true);
    CHECK(activePiece.size() == 2);
    CHECK(activePiece[0] == Puyo(Grid::red, 1, 0));
    CHECK(activePiece[1] == Puyo(Grid::green, 2, 0));
}

TEST_CASE("testing detection")
{
    std::vector<std::vector<Grid::PuyoType>> content(6, std::vector<Grid::PuyoType>(12));
    content[1][0] = Grid::red;
    content[1][1] = Grid::red;
    content[2][0] = Grid::red;
    content[3][0] = Grid::red;

    Grid grid = Grid(content);
    std::vector<Coordinates> starts{Coordinates(2, 0)};
    std::vector<std::vector<Puyo>> detected = runDetection(grid, starts);

    // to ensure grid.content has not been altered
    CHECK(detected.size() == 1);
    for (std::size_t x; x < grid.width(); x++)
        for (std::size_t y; y < grid.height(); y++)
            CHECK(grid.content[x][y] == content[x][y]);
}
