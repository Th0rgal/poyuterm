#include <doctest/doctest.h>
#include "controllers/activePiece.hpp"

TEST_CASE("testing shift")
{
    std::vector<std::vector<Grid::PuyoType>> content(6, std::vector<Grid::PuyoType>(12));

    ActivePiece activePiece(
        Puyo(Grid::red, 1, 0),
        Puyo(Grid::green, 2, 0), 0);

    Grid grid = Grid(content);
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

TEST_CASE("testing rotate")
{
    std::vector<std::vector<Grid::PuyoType>> content(6, std::vector<Grid::PuyoType>(12));

    ActivePiece activePiece{
        Puyo(Grid::red, 2, 0),
        Puyo(Grid::green, 1, 0), 0};

    Grid grid = Grid(content);

    bool moved = activePiece.rotate(grid);
    CHECK(moved == true);
    CHECK(activePiece.center == Puyo(Grid::red, 1, 0));
    CHECK(activePiece.side == Puyo(Grid::green, 1, 1));

    moved = activePiece.rotate(grid);
    CHECK(moved == true);
    CHECK(activePiece.center == Puyo(Grid::red, 1, 0));
    CHECK(activePiece.side == Puyo(Grid::green, 2, 0));

    moved = activePiece.rotate(grid);
    CHECK(moved == true);
    CHECK(activePiece.center == Puyo(Grid::red, 1, 1));
    CHECK(activePiece.side == Puyo(Grid::green, 1, 0));

    moved = activePiece.rotate(grid);
    CHECK(moved == true);
    CHECK(activePiece.center == Puyo(Grid::red, 2, 0));
    CHECK(activePiece.side == Puyo(Grid::green, 1, 0));

    moved = activePiece.rotate(grid, 4);
    CHECK(moved == true);
    CHECK(activePiece.center == Puyo(Grid::red, 2, 0));
    CHECK(activePiece.side == Puyo(Grid::green, 1, 0));

    moved = activePiece.rotate(grid, 3);
    CHECK(moved == true);
    CHECK(activePiece.center == Puyo(Grid::red, 1, 1));
    CHECK(activePiece.side == Puyo(Grid::green, 1, 0));

    activePiece = ActivePiece{
        Puyo(Grid::red, 5, 0),
        Puyo(Grid::green, 5, 1), 1};
    moved = activePiece.rotate(grid, 1);
    CHECK(moved == false);
}