#pragma once
#include <functional>
#include "domains/gameData.hpp"
#include "domains/grid.hpp"

class InputsListener
{
public:
    InputsListener(GameData &gameData, Grid &grid);
    void handleInputs(const std::function<void(int)> &loop);
    void shift(int x, int y);

private:
    GameData &gameData;
    Grid &grid;
    void onKeyPressed(int code);
    void translateLeft();
    void translateRight();
    void translateDown();
};