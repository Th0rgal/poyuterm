#include <doctest/doctest.h>
#include "domains/grid.hpp"
#include "domains/gameData.hpp"
#include "controllers/inputsListener.hpp"
#include <iostream>

TEST_CASE("testing shift")
{
    std::vector<std::vector<Grid::PuyoType>> content(6, std::vector<Grid::PuyoType>(12));
    content[1][0] = Grid::red;
    content[2][0] = Grid::green;

    std::vector<Puyo> activePiece = {
        Puyo(Grid::red, 1, 0),
        Puyo(Grid::red, 2, 0)};

    Grid grid = Grid(content);
    GameData gameData = GameData();
    gameData.activePiece = activePiece;
    InputsListener inputsListener(gameData, grid);

    inputsListener.shift(1, 0);
    std::vector<std::vector<Grid::PuyoType>> expectedContent(6, std::vector<Grid::PuyoType>(12));
    expectedContent[2][0] = Grid::red;
    expectedContent[3][0] = Grid::green;
    Grid expectedGrid = Grid(expectedContent);

    for (std::size_t x = 0; x < expectedGrid.width(); x++)
        for (std::size_t y = 0; y < expectedGrid.height(); y++)
            CHECK(expectedContent[x][y] == inputsListener.grid.content[x][y]);

    inputsListener.shift(0, 0);
    for (std::size_t x = 0; x < expectedGrid.width(); x++)
        for (std::size_t y = 0; y < expectedGrid.height(); y++)
        {
            std::cout << x << ":" << y << std::endl;
            CHECK(expectedContent[x][y] == inputsListener.grid.content[x][y]);
        }
}
