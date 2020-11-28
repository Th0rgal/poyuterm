#pragma once
#include <functional>
#include "models/gameData.hpp"
#include "models/grid.hpp"

class InputsListener
{
public:
    InputsListener(GameData &gameDataRef, Display &display, Grid &gridRef);
    void handleInputs(const std::function<void(long)> &loop);
    GameData &gameData;
    Display &display;
    Grid &grid;

private:
    //menu related
    void onMenuKeyPressed(int code);
    void menuUp();
    void menuDown();
    void menuEnter();

    // grid related
    void onPuyoKeyPressed(int code);
    void onTetrixKeyPressed(int code);
    bool translateLeft();
    bool translateRight();
    bool translateDown();
    void teleportDown();
    bool rotatePiece();
    void openMenu();
};