#include "controllers/inputsListener.hpp"
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
        teleportDown();
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
 * to teleport the active piece to the bottom if it is possible
 * 
 * @author Thomas Marchand
 **/
void InputsListener::teleportDown()
{
    // erase active Piece from displau
    for (Puyo puyo : gameData.activePiece)
        (*display.game).setCell(puyo.x, puyo.y, Grid::none);
    // snapshot grid content
    auto contentSnapshot = grid.content;

    // virtually move active Piece
    bool teleport;
    do
    {
        teleport = shift(gameData.activePiece, grid, 0, 1);
    } while (teleport);

    // write active piece to the grid and save coordinates
    std::vector<Coordinates> starts;
    for (Puyo puyo : gameData.activePiece)
    {
        grid.content[puyo.x][puyo.y] = puyo.type;
        starts.emplace_back(puyo.x, puyo.y);
    }

    // reset activePiece
    gameData.activePiece = {};

    // recursively find "destroyable" groups of Puyo and
    // remove them from the grid
    auto detected = runDetection(grid, starts);
    for (std::vector<Puyo> group : detected)
        for (Puyo puyo : group)
        {
            if (grid.content[puyo.x][puyo.y])
                break;
            grid.content[puyo.x][puyo.y] = Grid::none;
        }

    bool finished = false;
    while (!finished)
        finished = runGravity(grid);

    // refresh display
    (*display.game).refreshDiff(contentSnapshot, grid);
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