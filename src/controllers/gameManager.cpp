#include "controllers/gameManager.hpp"
#include "domains/gameData.hpp"
#include "domains/grid.hpp"
#include "views/display.hpp"

void loop()
{
    vector<vector<Grid::PuyoType>> content(6, vector<Grid::PuyoType>(12));

    // load domains
    GameData gameData = GameData();
    Grid grid = Grid(content);

    // load views
    ConsoleDisplay display = ConsoleDisplay();

    display.start();
}