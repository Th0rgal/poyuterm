#include "controllers/gameManager.hpp"
#include "controllers/inputsListener.hpp"
#include <stdlib.h>

GameManager::GameManager(GameData &gameDataRef, Grid &gridRef, ConsoleDisplay &displayRef) : gameData(gameDataRef), grid(gridRef), display(displayRef), rd(), gen(rd())
{
}

void GameManager::start()
{
    bool succeeded = (display).start();
    if (succeeded)
    {
        InputsListener inputsListener(gameData, grid);
        inputsListener.handleInputs([&](int delay) {
            loop(delay);
        });
        (display).close();
    }
    else
        (display).showError();
}

void GameManager::loop(long delay)
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

std::vector<std::pair<std::size_t, std::size_t>> GameManager::createNewPiece()
{
    std::size_t base = random_index(0, grid.width() - 1);
    std::vector<std::pair<std::size_t, std::size_t>> activePiece(2);
    activePiece[0] = std::pair<std::size_t, std::size_t>(base, 0);
    activePiece[1] = std::pair<std::size_t, std::size_t>(base + 1, 0);
    grid.content[0][base] = Grid::PuyoType(random_index(1, 5));
    grid.content[0][base + 1] = Grid::PuyoType(random_index(1, 5));
    return activePiece;
}

void GameManager::shiftActivePiece()
{
    std::vector<std::pair<std::size_t, std::size_t>> updatedPiece(2);
    for (std::size_t i = 0; i < gameData.activePiece.size(); i++)
    {
        updatedPiece[i] = gameData.activePiece[i];
        updatedPiece[i].second -= 1;
    }
    gameData.activePiece = updatedPiece;
}

std::size_t GameManager::random_index(std::size_t lower, std::size_t higher)
{
    std::uniform_int_distribution<std::size_t> dist(lower, higher);
    return dist(gen);
}