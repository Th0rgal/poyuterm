#include "controllers/gameManager.hpp"
#include "domains/gameData.hpp"
#include "domains/grid.hpp"

void loop()
{
    vector<vector<Grid::PuyoType>> content(6, vector<Grid::PuyoType>(12));
    GameData gameData = GameData();
    Grid grid = Grid(content);

    
}