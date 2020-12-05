#include "controllers/gameManager.hpp"
#include "controllers/gridTools.hpp"
#include "controllers/io/serializer.hpp"
#include <ncurses.h>

/**
 * to regenerate the activePiece when it is empty
 * 
 * @author Thomas Marchand
 * @confidence 3: this can't be tested (private)
 **/
void GameManager::puyoLoop(long delay)
{
    if (_gameData.activePiece.empty)
        _gameData.activePiece = createNewPiece();
}

/**
 * to bridge the different game mechanics of simulation with the display
 * @param long delay the delay in nanoseconds since last call
 * 
 * @author Thomas Marchand
 * @confidence 3 : this can't be tested (private)
 **/
void GameManager::simulationLoop(long delay)
{
    if (!parser.enabled)
        return;

    if (_gameData.delaySinceTick > 100000000l)
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