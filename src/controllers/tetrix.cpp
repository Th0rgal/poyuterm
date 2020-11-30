#include "controllers/gameManager.hpp"
#include "controllers/gridTools.hpp"
#include <bits/stdc++.h>

void GameManager::tetrixLoop(long delay)
{
    if (_gameData.activePiece.isEmpty())
        _gameData.activePiece = createNewPiece();

    if (_gameData.delaySinceTick > 300000000l) // in nanoseconds
    {

        std::vector<std::vector<Grid::PuyoType>> contentSnapshot = _grid.content;
        runGravity(_grid);
        (*_display.game).refreshDiff(contentSnapshot, _grid);

        ActivePiece clone = _gameData.activePiece;
        bool shifted = _gameData.activePiece.shift(_grid, 0, 1);
        if (!shifted)
        { // if we were already on the ground
            std::unordered_set<Coordinates> starts;
            _gameData.activePiece.map([&](Puyo &puyo) {
                _grid.content[puyo.x][puyo.y] = puyo.type;
                starts.emplace(puyo.x, puyo.y);
            });
            _gameData.activePiece.setEmpty();
            // delete groups
            std::vector<std::vector<Puyo>> groupsToDelete = runDetection(_grid, starts);
            for (std::vector<Puyo> group : groupsToDelete)
                for (Puyo puyo : group)
                {
                    _grid.content[puyo.x][puyo.y] = Grid::none;
                    (*_display.game).setCell(puyo.x, puyo.y, Grid::none);
                }
        }
        else
        {
            _gameData.delaySinceTick = 0;
            clone.map([&](Puyo &puyo) {
                (*_display.game).setCell(puyo.x, puyo.y, Grid::none);
            });

            _gameData.activePiece.map([&](Puyo &puyo) {
                (*_display.game).setCell(puyo.x, puyo.y, puyo.type);
            });
        }
    }
    else
        _gameData.delaySinceTick += delay;
}