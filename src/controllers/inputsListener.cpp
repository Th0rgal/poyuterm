#include "controllers/inputsListener.hpp"
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
 **/
InputsListener::InputsListener(GameData &gameData,
                               Display &display,
                               Grid &grid) : display(display),
                                             gameData(gameData),
                                             grid(grid)
{
}

/**
 * to handle user inputs while callig the game loop
 * @param std::function<void(long)> loop the game loop function (callback)
 * 
 * @author Thomas Marchand
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
            switch (gameData.mode)
            {
            case GameData::menu:
                onMenuKeyPressed(inputCode);
                break;
            case GameData::solo:
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