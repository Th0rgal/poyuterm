#include "controllers/gameManager.hpp"
#include "controllers/inputsListener.hpp"

GameManager::GameManager(GameData &gameData, Grid &grid, ConsoleDisplay &display) : gameData(gameData), grid(grid), display(display)
{
}

void GameManager::start()
{
    bool succeeded = (display).start();
    if (succeeded)
    {
        handleInputs([&](double delay) {
            loop(delay);
        });
        (display).close();
    }
    else
        (display).showError();
}

void GameManager::loop(double delay)
{
    gameData.activePiece;
}