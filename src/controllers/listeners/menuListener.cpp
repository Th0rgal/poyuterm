#include "controllers/listeners/inputsListener.hpp"

/**
 * interactive function between menu and key
 *
 * @param int code key to chack
 * @param GameData::GameState menuType menu to use
 * @param usigned int score score for easter egg
 * 
 * @author Valeran MAYTIE
 * @confidence 3: impossible to test listeners
 **/
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

/**
 * Open menu Start and change _gameFata.state
 * 
 * @author Valeran MAYTIE
 * @confidence 3: impossible to test listeners
 **/
void InputsListener::openMenuStart()
{
    _gameData.state = GameData::menu;
    _display.showMenuStart();
}

/**
 * Open menu Start and change _gameFata.state and stop music
 * 
 * @author Valeran MAYTIE
 * @confidence 3: impossible to test listeners
 **/
void InputsListener::openMenuOver()
{
    _music.PausedMusicGame();
    _display.showMenuEnd(_gameData.score);
}

/**
 * mounted menu cursor and play sound effects
 * 
 * @param GameData::GameState menuType menu to use
 * @author Valeran MAYTIE
 * @confidence 3: impossible to test listeners
 **/
void InputsListener::menuUp(GameData::GameState menuType)
{
    _music.menuChangePlay();
    (*_display.menu).previous(menuType);
}

/**
 * go down menu cursor and play sound effects
 * 
 * @param GameData::GameState menuType menu to use
 * @author Valeran MAYTIE
 * @confidence 3: impossible to test listeners
 **/
void InputsListener::menuDown(GameData::GameState menuType)
{
    _music.menuChangePlay();
    (*_display.menu).next(menuType);
}

/**
 * Select iteam in menu
 * 
 * @author Valeran MAYTIE and Thomas MARCHAND
 * @confidence 3: impossible to test listeners
 **/
void InputsListener::menuEnterStart()
{
    unsigned int selected = (*_display.menu).select(2);
    if (selected == 3)
    {
        //_display.close();
        coninueGame = false;
        return;
    }
    _music.startMusicGame(selected);
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

/**
 * Select iteam in menu over
 *
 * @author Valeran MAYTIE
 * @confidence 3: impossible to test listeners
 **/
void InputsListener::menuEnterOver()
{
    unsigned int selected = (*_display.menu).select(3);
    if (selected == 1)
    {
        //_display.close();
        coninueGame = false;
        return;
    }
    openMenuStart();
}