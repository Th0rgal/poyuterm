#pragma once
#include <functional>
#include "domains/gameData.hpp"
#include "domains/grid.hpp"

class InputsListener
{
public:
    InputsListener(GameData &gameDataRef, Grid &gridRef);
    void handleInputs(const std::function<void(long)> &loop);
    void shift(int x, int y);
    GameData &gameData;
    Grid &grid;

private:
    void onKeyPressed(int code);
    void translateLeft();
    void translateRight();
    void translateDown();
};