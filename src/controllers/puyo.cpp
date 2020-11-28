#include "controllers/gameManager.hpp"

void GameManager::puyoLoop(long delay)
{
    if (gameData.activePiece.empty())
        gameData.activePiece = createNewPiece();
}