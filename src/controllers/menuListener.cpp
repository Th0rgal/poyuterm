#include "controllers/inputsListener.hpp"
#include "views/display.hpp"

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
    unsigned int selected = (*display.menu).select();
    if (selected == 4)
    {
        display.close();
        exit(0);
        return;
    }

    GameData::GameMode newGameMode = GameData::GameMode(selected);
    gameData.mode = newGameMode;
    display.showGame();
}