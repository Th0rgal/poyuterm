#include "controllers/listeners/inputsListener.hpp"
#include "views/display.hpp"
#include <chrono>

using namespace std::chrono;

/**
 * to intialize the InputsListener with game and grid models
 * @param GameData &gameData the GameData instance
 * @param Display display the Display instance
 * @param Grid &grid the Grid instance
 * 
 * @author Thomas Marchand
 * @confidence 3: impossible to test listeners
 **/
InputsListener::InputsListener(GameData &gameData,
                               Display &display,
                               Grid &grid) : _gameData(gameData),
                                             _display(display),
                                             _grid(grid)
{
}

/**
 * to handle user inputs while callig the game loop
 * @param std::function<void(long)> loop the game loop function (callback)
 * 
 * @author Thomas Marchand
 * @confidence 3: impossible to test listeners
 **/
void InputsListener::handleInputs(const std::function<void(long)> &loop)
{
    int inputCode;
    high_resolution_clock::time_point previousTime = high_resolution_clock::now();
    while ((inputCode = getch()) != 'q')
    {
        if (inputCode == ERR)
        {
            loop(duration_cast<nanoseconds>(high_resolution_clock::now() - previousTime).count());
            previousTime = high_resolution_clock::now();
        }
        else
        {
            if (_gameData.state == GameData::menu ){
                onMenuKeyPressed(inputCode, _gameData.state, 1);
            }else if(_gameData.state == GameData::ended){
                openMenuOver();
                onMenuKeyPressed(inputCode, _gameData.state, _gameData.score);
            }
            else if (inputCode == 'P' or inputCode == 'p')
            {
                _music.PausedMusicGame();
                openMenuStart();
            }
            else if (_gameData.state == GameData::running){
                switch (_gameData.mode)
                {
                case GameData::solo:
                    onPuyoKeyPressed(inputCode);
                    break;
                case GameData::tetrix:
                    onTetrixKeyPressed(inputCode);
                    break;
                default:
                    break;
                }
            }
        }
    }
}