#pragma once

#include <functional>
#include "models/gameData.hpp"
#include "models/grid.hpp"
#include "views/display.hpp"
#include "views/music/music.hpp"

class InputsListener
{
public:
    InputsListener(GameData &gameData, Display &display, Grid &grid);
    void handleInputs(const std::function<void(long)> &loop);
    GameData &_gameData;
    Display &_display;
    Grid &_grid;
    CAudio _music{};

private:
    //menu related
    void onMenuKeyPressed(int code, GameData::GameState menuType, unsigned int score);
    void menuUp(GameData::GameState menuType);
    void menuDown(GameData::GameState menuType);
    void menuEnterStart();
    void menuEnterOver();

    // grid related
    void onPuyoKeyPressed(int code);
    void onTetrixKeyPressed(int code);
    bool translateLeft();
    bool translateRight();
    bool translateDown();
    bool rotatePiece();
    void openMenuStart();
    void openMenuOver();
};