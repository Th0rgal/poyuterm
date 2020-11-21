#include "controllers/gameManager.hpp"
#include "domains/gameData.hpp"
#include "domains/grid.hpp"
#include "views/display.hpp"

int main()
{
    // todo: read a file
    std::vector<std::vector<Grid::PuyoType>> content(6, std::vector<Grid::PuyoType>(12));

    // load domains
    GameData gameData = GameData();
    Grid grid = Grid(content);

    // load views
    ConsoleDisplay display = ConsoleDisplay();

    // load controllers
    GameManager(gameData, grid, display).start();

    return 0;
}