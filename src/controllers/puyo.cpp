#include "controllers/gameManager.hpp"
#include "controllers/gridTools.hpp"
#include "controllers/io/serializer.hpp"
#include <ncurses.h>

void GameManager::puyoLoop(long delay)
{
    if (_gameData.activePiece.empty)
        _gameData.activePiece = createNewPiece();
}

void GameManager::simulationLoop(long delay)
{
    if (!parser.enabled)
        return;

    if (_gameData.delaySinceTick > 300000000l)
    {
        if (_gameData.activePiece.empty)
        {
            if (!parser.next(_grid))
            {
                _gameData.state = GameData::ended;
                Serializer serializer("sortie.txt");
                serializer.writeGrid(_grid);
                serializer.writeScore(_gameData.score);
                return;
            }
            _gameData.activePiece = parser.activePiece;
            _gameData.activePiece.map([&](Puyo &puyo) { (*_display.game).setCell(puyo.x, puyo.y, puyo.type); });
        }
        else
        {
            _gameData.activePiece.map([&](Puyo &puyo) { (*_display.game).setCell(puyo.x, puyo.y, Grid::none); });
            teleportDown(_grid, _gameData, _display);
        }

        _gameData.delaySinceTick = 0;
    }
    else
        _gameData.delaySinceTick += delay;
}