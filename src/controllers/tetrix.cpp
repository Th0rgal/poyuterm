#include "controllers/gameManager.hpp"
#include "controllers/gridTools.hpp"
#include <bits/stdc++.h>

void GameManager::tetrixLoop(long delay)
{
    if (gameData.activePiece.isEmpty())
        gameData.activePiece = createNewPiece();

    if (gameData.delaySinceTick > 300000000l) // in nanoseconds
    {

        std::vector<std::vector<Grid::PuyoType>> contentSnapshot = grid.content;
        runGravity(grid);
        (*display.game).refreshDiff(contentSnapshot, grid);

        ActivePiece clone = gameData.activePiece;
        bool shifted = gameData.activePiece.shift(grid, 0, 1);
        if (!shifted)
        { // if we were already on the ground
            std::unordered_set<Coordinates> starts;
            gameData.activePiece.map([&](Puyo &puyo) {
                grid.content[puyo.x][puyo.y] = puyo.type;
                starts.emplace(puyo.x, puyo.y);
            });
            gameData.activePiece.setEmpty();
            // delete groups
            std::vector<std::vector<Puyo>> groupsToDelete = runDetection(grid, starts);
            for (std::vector<Puyo> group : groupsToDelete)
                for (Puyo puyo : group)
                {
                    grid.content[puyo.x][puyo.y] = Grid::none;
                    (*display.game).setCell(puyo.x, puyo.y, Grid::none);
                }
        }
        else
        {
            gameData.delaySinceTick = 0;
            clone.map([&](Puyo &puyo) {
                (*display.game).setCell(puyo.x, puyo.y, Grid::none);
            });

            gameData.activePiece.map([&](Puyo &puyo) {
                (*display.game).setCell(puyo.x, puyo.y, puyo.type);
            });
        }
    }
    else
        gameData.delaySinceTick += delay;
}