#include "controllers/gameManager.hpp"
#include "controllers/gridTools.hpp"
#include "controllers/io/serializer.hpp"
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
            if (!parser.next(grid))
            {
                gameData.state = GameData::ended;
                Serializer serializer("sortie.txt");
                serializer.writeGrid(grid);
                serializer.writeScore(gameData.score);
                return;
            }
            gameData.activePiece = parser.activePiece;
            for (Puyo puyo : gameData.activePiece)
                (*display.game).setCell(puyo.x, puyo.y, puyo.type);
        }
        else
        {
            for (Puyo puyo : gameData.activePiece)
                (*display.game).setCell(puyo.x, puyo.y, Grid::none);
            teleportDown(grid, gameData, display);
        }

        gameData.delaySinceTick = 0;
    }
    else
        gameData.delaySinceTick += delay;
}