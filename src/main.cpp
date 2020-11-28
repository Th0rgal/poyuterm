#include "controllers/gameManager.hpp"
#include "models/gameData.hpp"
#include "models/grid.hpp"

int main()
{
    // todo: read a file
    std::vector<std::vector<Grid::PuyoType>> content(6, std::vector<Grid::PuyoType>(12));

    // load models
    GameData gameData = GameData();
    Grid grid = Grid(content);

    // load controllers
    GameManager(gameData, grid).start();

    return 0;
}