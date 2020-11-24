#include <ncurses.h>
#include <functional>
#include "controllers/inputsListener.hpp"
#include <chrono>
#include <algorithm>
#include <iostream>

using namespace std::chrono;

/**
 * to intialize the InputsListener with game and grid domains
 * @param GameData gameDataRef the GameData instance
 * @param Grid gridRef the Grid instance
 **/
InputsListener::InputsListener(GameData &gameDataRef,
                               Grid &gridRef) : gameData(gameDataRef),
                                                grid(gridRef)
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
    shift(-1, 0);
}

/**
 * to shift the falling piece to the right (one case) if it is possible
 **/
void InputsListener::translateRight()
{
    shift(1, 0);
}

/**
 * to shift the falling piece to the bottom (one case) if it is possible
 **/
void InputsListener::translateDown()
{
    shift(0, -1);
}

/**
 * to shift the falling piece in gameData and on the grid
 * @param int x, -1 <= x <= 1, the shift on the x axis
 * @param int y, -1 <= y <= 1, the shift on the y axis
 **/
void InputsListener::shift(int x, int y)
{
    const size_t size = gameData.activePiece.size();
    std::vector<Puyo> updatedPiece(size);

    for (size_t i = 0; i < size; i++)
    {
        Puyo piecePart = gameData.activePiece[i];

        // avoid impossible x
        if (piecePart.x < static_cast<unsigned int>(x) ||
            static_cast<int>(piecePart.x) + x >= static_cast<int>(grid.width()))
            return;

        // avoid impossible y
        if (piecePart.y < static_cast<unsigned int>(y) ||
            static_cast<int>(piecePart.y) + y >= static_cast<int>(grid.height()))
            return;

        std::size_t previousX = piecePart.x;
        std::size_t previousY = piecePart.y;
        piecePart.add(static_cast<unsigned int>(x), static_cast<unsigned int>(y));

        // avoid overwriting
        if (grid.content[piecePart.x][piecePart.y])
            return;

        updatedPiece[i] = piecePart;
    }

    gameData.activePiece = updatedPiece;
}