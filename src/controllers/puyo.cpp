#include "controllers/gameManager.hpp"

void GameManager::puyoLoop(long delay)
{
    if (gameData.activePiece.empty())
        gameData.activePiece = createNewPiece();
}

void GameManager::simulationLoop(long delay)
{
    if (gameData.delaySinceTick > 300000000l)
    {
    }
    else
        gameData.delaySinceTick += delay;
}