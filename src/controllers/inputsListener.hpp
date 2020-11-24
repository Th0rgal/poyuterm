#pragma once
#include <functional>
#include "domains/gameData.hpp"
#include "domains/grid.hpp"

class InputsListener
{
public:
    InputsListener(GameData &gameDataRef, ConsoleDisplay &consoleDisplay, Grid &gridRef);
    void handleInputs(const std::function<void(long)> &loop);
    GameData &gameData;
    ConsoleDisplay &consoleDisplay;
    Grid &grid;

private:
    void onKeyPressed(int code);
    bool translateLeft();
    bool translateRight();
    bool translateDown();
};