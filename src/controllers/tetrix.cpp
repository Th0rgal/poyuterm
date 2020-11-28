#include "controllers/gameManager.hpp"
#include "controllers/gridTools.hpp"

void GameManager::tetrixLoop(long delay)
{
    if (gameData.activePiece.empty())
        gameData.activePiece = createNewPiece();

    if (gameData.delaySinceGravity > 300000000l) // in nanoseconds
    {

        std::vector<std::vector<Grid::PuyoType>> contentSnapshot = grid.content;
        runGravity(grid);
        (*display.game).refreshDiff(contentSnapshot, grid);

        const std::vector<Puyo> clone = gameData.activePiece;
        bool shifted = shift(gameData.activePiece, grid, 0, 1);
        if (!shifted)
        { // if we were already on the ground
            std::vector<Coordinates> starts;
            for (Puyo puyo : gameData.activePiece)
            {
                grid.content[puyo.x][puyo.y] = puyo.type;
                starts.emplace_back(puyo.x, puyo.y);
            }
            gameData.activePiece = {};
            // delete groups
            std::vector<std::vector<Puyo>> groupsToDelete = runDetection(grid, starts);
            for (std::vector<Puyo> group : groupsToDelete)
                for (Puyo puyo : group)
                {
                    if (!puyo.type)
                        break;

                    grid.content[puyo.x][puyo.y] = Grid::none;
                    (*display.game).setCell(puyo.x, puyo.y, Grid::none);
                }
        }
        else
        {
            gameData.delaySinceGravity = 0;
            for (Puyo puyo : clone)
                (*display.game).setCell(puyo.x, puyo.y, Grid::none);
            for (Puyo puyo : gameData.activePiece)
                (*display.game).setCell(puyo.x, puyo.y, puyo.type);
        }
    }
    else
        gameData.delaySinceGravity += delay;
}