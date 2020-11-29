#include "controllers/listeners/inputsListener.hpp"
#include "views/display.hpp"


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
    gameData.state = GameData::menu;
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
    unsigned int selected = (*display.menu).select();
    if (selected == 3)
    {
        display.close();
        exit(0);
        return;
    }
    GameData::GameMode newGameMode = GameData::GameMode(selected);
    auto contentSnapshot = grid.content;
    gameData.state = GameData::running;
    display.showGame();
    if (gameData.mode != newGameMode)
    {
        gameData.mode = newGameMode;
        grid.reset();
        for (Puyo puyo : gameData.activePiece)
            (*display.game).setCell(puyo.x, puyo.y, Grid::none);
        gameData.activePiece = {};
        (*display.game).refreshDiff(contentSnapshot, grid);
    }
}