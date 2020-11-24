#include <doctest/doctest.h>
#include "domains/grid.hpp"
#include "domains/gameData.hpp"

#include <iostream>

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

}
