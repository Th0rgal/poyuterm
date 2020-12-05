#include <doctest/doctest.h>
#include "controllers/io/parser.hpp"

TEST_CASE("testing parser")
{
    Parser parser;
    CHECK(parser.enabled == false);

    parser = Parser{"./tests/inputs/example_simulation.txt"};
    CHECK(parser.enabled == true);
    CHECK(parser.gameMode == GameData::simulation);

    std::vector<std::vector<Grid::PuyoType>> content{12, std::vector<Grid::PuyoType>{12}};

    Grid grid = Grid(content);
    bool worked = parser.next(grid);
    CHECK(worked);
    CHECK(parser.activePiece.center.x == 1);
    CHECK(parser.activePiece.center.y == 0);
    CHECK(parser.activePiece.side.x == 0);
    CHECK(parser.activePiece.side.y == 0);
    CHECK(parser.activePiece._orientation == 0);
}