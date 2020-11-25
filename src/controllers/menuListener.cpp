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
    GameData::GameMode newGameMode = GameData::GameMode((*display.menu).select());
    gameData.mode = newGameMode;
    display.showGame();
}