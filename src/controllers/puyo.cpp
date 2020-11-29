#include "controllers/gameManager.hpp"
#include "controllers/gridTools.hpp"
#include <ncurses.h>

void GameManager::puyoLoop(long delay)
{
    if (gameData.activePiece.empty())
        gameData.activePiece = createNewPiece();
}

void GameManager::simulationLoop(long delay)
{
    if (!parser.enabled)
        return;

    if (gameData.delaySinceTick > 300000000l)
    {
        if (gameData.activePiece.empty())
        {
            parser.next(grid);
            gameData.activePiece = parser.activePiece;
        }
        else
            teleportDown(grid, gameData, display);

        gameData.delaySinceTick = 0;
    }
    else
        gameData.delaySinceTick += delay;
}