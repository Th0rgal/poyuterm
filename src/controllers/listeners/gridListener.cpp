#include "controllers/listeners/inputsListener.hpp"
#include "views/display.hpp"
#include "controllers/gridTools.hpp"
#include <ncurses.h>

void InputsListener::onPuyoKeyPressed(int code)
{
    const std::vector<Puyo> clone = gameData.activePiece;
    bool shifted = false;
    switch (code)
    {

    case 'P':
    case 'p':
        openMenu();
        break;

    case KEY_LEFT:
        shifted = translateLeft();
        break;

    case KEY_RIGHT:
        shifted = translateRight();
        break;

    case KEY_DOWN:
        teleportDown(grid, gameData, display);
        break;

    case ' ':
        shifted = rotatePiece();
        break;

    default:
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
 * to translate user inputs to actions (e.g. movements on the grid)
 * @param int code the key code
 * 
 * @author Thomas Marchand and Valeran Maytié
 **/
void InputsListener::onTetrixKeyPressed(int code)
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
        shifted = rotatePiece();
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
bool InputsListener::rotatePiece()
{
    return rotate(gameData.activePiece, grid);
}