#include "controllers/gameManager.hpp"
#include "controllers/gridTools.hpp"
#include "controllers/io/serializer.hpp"
#include <ncurses.h>

void GameManager::puyoLoop(long delay)
{
    if (gameData.activePiece.isEmpty())
        gameData.activePiece = createNewPiece();
}

void GameManager::simulationLoop(long delay)
{
    if (!parser.enabled)
        return;

    if (gameData.delaySinceTick > 300000000l)
    {
        if (gameData.activePiece.isEmpty())
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
            gameData.activePiece.map([&](Puyo &puyo) { (*display.game).setCell(puyo.x, puyo.y, puyo.type); });
        }
        else
        {
            gameData.activePiece.map([&](Puyo &puyo) { (*display.game).setCell(puyo.x, puyo.y, Grid::none); });
            teleportDown(grid, gameData, display);
        }

        gameData.delaySinceTick = 0;
    }
    else
        gameData.delaySinceTick += delay;
}