#include <functional>
#include "controllers/inputsListener.hpp"
#include "views/display.hpp"
#include "views/menuscreen.hpp"
#include <chrono>
#include <algorithm>
#include <iostream>

using namespace std::chrono;

/**
 * to intialize the InputsListener with game and grid domains
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
            if (gameData.state != GameData::paused)
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
            case GameData::tetris:
                onTetrisKeyPressed(inputCode);
                break;
            default:
                break;
            }
        }
    }
}

/**
 * to translate user inputs to actions (e.g. movements on the grid)
 * @param int code the key code
 * 
 * @author Thomas Marchand and Valeran Maytié
 **/
void InputsListener::onTetrisKeyPressed(int code)
{
    const std::vector<Puyo> clone = gameData.activePiece;
    bool shifted;
    switch (code)
    {

    case 'P':
    case 'p':
        openMenu();
        shifted = false;
        break;

    case KEY_LEFT:
        shifted = translateLeft();
        break;

    case KEY_RIGHT:
        shifted = translateRight();
        break;

    case KEY_DOWN:
        shifted = translateDown();
        break;

    case ' ':
        shifted = translateDown();
        break;

    default:
        shifted = false;
        break;
    };
    if (shifted)
    {
        for (Puyo puyo : clone)
            (*display.game).setCell(puyo.x, puyo.y, Grid::none);
        for (Puyo puyo : gameData.activePiece)
            (*display.game).setCell(puyo.x, puyo.y, puyo.type);
    }
}

/**
 * to shift the falling piece to the left (one case) if it is possible
 * 
 * @author Thomas Marchand
 **/
bool InputsListener::translateLeft()
{
    return shift(gameData.activePiece, grid, -1, 0);
}

/**
 * to shift the falling piece to the right (one case) if it is possible
 * 
 * @author Thomas Marchand
 **/
bool InputsListener::translateRight()
{
    return shift(gameData.activePiece, grid, 1, 0);
}

/**
 * to shift the falling piece to the bottom (one case) if it is possible
 * 
 * @author Thomas Marchand
 **/
bool InputsListener::translateDown()
{
    return shift(gameData.activePiece, grid, 0, 1);
}

/**
 * to rotate the falling piece clockwisely
 * 
 * @author Valeran Maytié
 **/
bool InputsListener::rotate()
{
    return true;
}

void InputsListener::onMenuKeyPressed(int code)
{
    switch (code)
    {

    case KEY_UP:
        menuUp();
        break;

    case KEY_DOWN:
        menuDown();
        break;

    case '\n':
        menuEnter();
        break;
    };
}

void InputsListener::openMenu()
{
    gameData.mode = GameData::menu;
    display.showMenu();
}

void InputsListener::menuUp()
{
    (*display.menu).previous();
}

void InputsListener::menuDown()
{
    (*display.menu).next();
}

void InputsListener::menuEnter()
{
    GameData::GameMode newGameMode = GameData::GameMode((*display.menu).select());
    gameData.mode = newGameMode;
    display.showGame();
}