#include "controllers/listeners/inputsListener.hpp"

void InputsListener::onMenuKeyPressed(int code, GameData::GameState menuType, unsigned int score)
{
    switch (code)
    {
    case KEY_UP:
        menuUp(menuType);
        break;

    case KEY_DOWN:
        menuDown(menuType);
        break;

    case '\n':
        if(menuType == 2)
            menuEnterStart();
        else
            menuEnterOver();
        
        break;
    case 'c':
        if(menuType != 2 && score == 0){
            _music.easterEggsPlay();
        }
        break;
    };
}

void InputsListener::openMenuStart()
{
    _gameData.state = GameData::menu;
    _display.showMenuStart();
}

void InputsListener::openMenuOver()
{
    _music.PausedMusicGame();
    _display.showMenuEnd(_gameData.score);
}

void InputsListener::menuUp(GameData::GameState menuType)
{
    _music.menuChangePlay();
    (*_display.menu).previous(menuType);
}

void InputsListener::menuDown(GameData::GameState menuType)
{
    _music.menuChangePlay();
    (*_display.menu).next(menuType);
}

void InputsListener::menuEnterStart()
{
    unsigned int selected = (*_display.menu).select(2);
    if (selected == 3)
    {
        _display.close();
        exit(0);
        return;
    }
    _music.startMusicGame();
    GameData::GameMode newGameMode = GameData::GameMode(selected);
    auto contentSnapshot = _grid.content;
    _gameData.state = GameData::running;
    _display.showGame();
    if (_gameData.mode != newGameMode)
    {
        _gameData.mode = newGameMode;
        _grid.reset();

        _gameData.activePiece.map([&](Puyo &puyo) {
            (*_display.game).setCell(puyo.x, puyo.y, Grid::none);
        });
        _gameData.activePiece.empty = true;
        (*_display.game).refreshDiff(contentSnapshot, _grid);
    }
}

void InputsListener::menuEnterOver()
{
    unsigned int selected = (*_display.menu).select(3);
    if (selected == 1)
    {
        _display.close();
        exit(0);
        return;
    }
    openMenuStart();
}