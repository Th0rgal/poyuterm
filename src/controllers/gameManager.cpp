#include "controllers/gameManager.hpp"
#include "controllers/inputsListener.hpp"
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

GameManager::GameManager(GameData &gameData, Grid &grid, ConsoleDisplay &display) : gameData(gameData), grid(grid), display(display)
{
    srand(time(NULL));
}

void GameManager::start()
{
    bool succeeded = (display).start();
    if (succeeded)
    {
        handleInputs([&](int delay) {
            loop(delay);
        });
        (display).close();
    }
    else
        (display).showError();
}

void GameManager::loop(int delay)
{
    if (gameData.activePiece.empty())
        gameData.activePiece = createNewPiece();

    if (gameData.delaySinceGravity > 1000) // in milliseconds
    {
        bool falling = grid.triggerGravity();
        if (!falling)
            gameData.activePiece = {};
        else
            shiftActivePiece();
        gameData.delaySinceGravity = 0;
    }
    else
        gameData.delaySinceGravity += delay;
}

std::vector<std::pair<int, int>> GameManager::createNewPiece()
{
    int base = rand() % (grid.width() - 1);
    std::vector<std::pair<int, int>> activePiece(2);
    activePiece[0] = std::pair<int, int>(base, 0);
    activePiece[1] = std::pair<int, int>(base + 1, 0);
    grid.content[0][base] = Grid::PuyoType(rand() % 5 + 1);
    grid.content[0][base + 1] = Grid::PuyoType(rand() % 5 + 1);
    return activePiece;
}

void GameManager::shiftActivePiece()
{
    std::vector<std::pair<int, int>> updatedPiece(2);
    for (int i = 0; i < gameData.activePiece.size(); i++)
    {
        std::pair<int, int> coordinates = gameData.activePiece[i];
        coordinates.second -= 1;
    }
    gameData.activePiece = updatedPiece;
}