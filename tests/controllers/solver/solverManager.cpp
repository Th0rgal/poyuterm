#include <doctest/doctest.h>
#include "controllers/solver/solverManager.hpp"

// to check for errors
TEST_CASE("testing contructor")
{
    Parser parser{"./tests/inputs/example_ia.txt"};
    Solver solver{parser};
}

TEST_CASE("testing teleportation")
{
    Parser parser{"./tests/inputs/example_ia.txt"};
    Solver solver{parser};
    std::vector<std::vector<Grid::PuyoType>> content(6, std::vector<Grid::PuyoType>(12));
    Grid grid{content};
    ActivePiece piece{Puyo{Grid::red, 1, 2}, Puyo{Grid::red, 2, 2}, 2};

    unsigned int score = solver.teleportDownVirtually(grid, piece);
    CHECK(score == 0);
    piece = ActivePiece{Puyo{Grid::red, 1, 2}, Puyo{Grid::red, 2, 2}, 2};
    score = solver.teleportDownVirtually(grid, piece);
    CHECK(score == 280);
}

TEST_CASE("testing highest column size")
{
    Parser parser{"./tests/inputs/example_ia.txt"};
    Solver solver{parser};
    std::vector<std::vector<Grid::PuyoType>> content(6, std::vector<Grid::PuyoType>(12));
    content[4][11] = Grid::red;
    content[4][10] = Grid::blue;
    content[4][9] = Grid::green;
    content[3][11] = Grid::yellow;
    content[3][10] = Grid::yellow;
    Grid grid{content};
    CHECK(solver.computeHighestColumnSize(grid) == 3);
}

TEST_CASE("testing efficiency index")
{
    Parser parser{"./tests/inputs/example_ia.txt"};
    Solver solver{parser};
    std::vector<std::vector<Grid::PuyoType>> content(6, std::vector<Grid::PuyoType>(12));
    content[4][11] = Grid::red;
    content[4][10] = Grid::blue;
    content[4][9] = Grid::green;
    content[3][11] = Grid::yellow;
    content[3][10] = Grid::yellow;
    Grid grid{content};
    unsigned int highestColumnSize = solver.computeHighestColumnSize(grid);
    CHECK(solver.computeEfficiencyIndex(grid, highestColumnSize) == 2);
}

TEST_CASE("testing score")
{
    CHECK(getScore(1, 3, 5) == 3070);
    CHECK(getScore(2, 3, 4) == 2900);
    CHECK(getScore(3, 2, 3) == 1290);
}
