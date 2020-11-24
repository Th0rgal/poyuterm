#include <ncurses.h>
#include <functional>
#include "controllers/inputsListener.hpp"
#include "views/display.hpp"
#include <chrono>
#include <algorithm>
#include <iostream>

using namespace std::chrono;

/**
 * to intialize the InputsListener with game and grid domains
 * @param GameData gameDataRef the GameData instance
 * @param Grid gridRef the Grid instance
 **/
InputsListener::InputsListener(GameData &gameData,
                               ConsoleDisplay &consoleDisplay,
                               Grid &grid) : consoleDisplay(consoleDisplay),
                                             gameData(gameData),
                                             grid(grid)
{
}

/**
 * to handle user inputs while callig the game loop
 * @param std::function<void(long)> loop the game loop function
 **/
void InputsListener::handleInputs(const std::function<void(long)> &loop)
{
    int inputCode;
    high_resolution_clock::time_point previousTime = high_resolution_clock::now();
    while ((inputCode = getch()) != KEY_ENTER)
    {
        if (inputCode == ERR)
        {
            loop((high_resolution_clock::now() - previousTime).count() / 1000000l);
            previousTime = high_resolution_clock::now();
        }
        else
        {
            onKeyPressed(inputCode);
        }
    }
}

/**
 * to translate user inputs to actions (e.g. movements on the grid)
 * @param int code the key code
 **/
void InputsListener::onKeyPressed(int code)
{
    switch (code)
    {
    case KEY_LEFT:
        translateLeft();
        break;

    case KEY_RIGHT:
        translateRight();
        break;

    case KEY_DOWN:
        translateDown();
        break;

    default:
        break;
    }
}

/**
 * to shift the falling piece to the left (one case) if it is possible
 **/
void InputsListener::translateLeft()
{
    shift(gameData.activePiece, consoleDisplay, grid, -1, 0);
}

/**
 * to shift the falling piece to the right (one case) if it is possible
 **/
void InputsListener::translateRight()
{
    shift(gameData.activePiece, consoleDisplay, grid, 1, 0);
}

/**
 * to shift the falling piece to the bottom (one case) if it is possible
 **/
void InputsListener::translateDown()
{
    shift(gameData.activePiece, consoleDisplay, grid, 0, 1);
}
