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
 * @param GameData &gameData the GameData instance
 * @param ConsoleDisplay display the ConsoleDisplay instance
 * @param Grid &grid the Grid instance
 **/
InputsListener::InputsListener(GameData &gameData,
                               ConsoleDisplay &display,
                               Grid &grid) : display(display),
                                             gameData(gameData),
                                             grid(grid)
{
}

/**
 * to handle user inputs while callig the game loop
 * @param std::function<void(long)> loop the game loop function (callback)
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
    const std::vector<Puyo> clone = gameData.activePiece;
    bool shifted;
    switch (code)
    {
    case KEY_LEFT:
        shifted = translateLeft();
        break;

    case KEY_RIGHT:
        shifted = translateRight();
        break;

    case KEY_DOWN:
        shifted = translateDown();
        break;

    case KEY_BACKSPACE:
        shifted = rotate();
        break;

    default:
        shifted = false;
        break;
    };
    if (shifted)
    {
        for (Puyo puyo : clone)
            display.setCell(puyo.x, puyo.y, Grid::none);
        for (Puyo puyo : gameData.activePiece)
            display.setCell(puyo.x, puyo.y, puyo.type);
    }
}

/**
 * to shift the falling piece to the left (one case) if it is possible
 **/
bool InputsListener::translateLeft()
{
    return shift(gameData.activePiece, grid, -1, 0);
}

/**
 * to shift the falling piece to the right (one case) if it is possible
 **/
bool InputsListener::translateRight()
{
    return shift(gameData.activePiece, grid, 1, 0);
}

/**
 * to shift the falling piece to the bottom (one case) if it is possible
 **/
bool InputsListener::translateDown()
{
    return shift(gameData.activePiece, grid, 0, 1);
}

/**
 * to rotate the falling piece clockwisely
 **/
bool InputsListener::rotate()
{
    return true;
}
