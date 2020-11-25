#include "controllers/gameManager.hpp"
#include "domains/gameData.hpp"
#include "domains/grid.hpp"
#include "views/menu.hpp"

int main()
{
    // todo: read a file
    std::vector<std::vector<Grid::PuyoType>> content(6, std::vector<Grid::PuyoType>(12));

    // load domains
    GameData gameData = GameData();
    Grid grid = Grid(content);

    // load views

    // load controllers
    GameManager(gameData, grid).start();

    return 0;
}