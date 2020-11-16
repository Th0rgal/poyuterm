#include "controllers/gameManager.hpp"
#include "domains/grid.hpp"

void gameManager::loop()
{
    vector<vector<Grid::PuyoType>> content(6, vector<Grid::PuyoType>(12));
    Grid grid = Grid(content);
}