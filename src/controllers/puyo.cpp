#include "controllers/gameManager.hpp"

void GameManager::puyoLoop(long delay)
{
    switch (gameData.mode)
    {
    case GameData::solo:
        if (gameData.activePiece.empty())
            gameData.activePiece = createNewPiece();

    case GameData::simulation:
        break;

    default:
        break;
    }
}