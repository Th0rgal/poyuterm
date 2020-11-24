#include "controllers/gameManager.hpp"
#include "domains/gameData.hpp"
#include "controllers/inputsListener.hpp"
#include <stdlib.h>

GameManager::GameManager(GameData &gameDataRef,
                         Grid &gridRef,
                         ConsoleDisplay &displayRef) : gameData(gameDataRef),
                                                       grid(gridRef),
                                                       display(displayRef),
                                                       rd(),
                                                       gen(rd())
{
}

void GameManager::start()
{
    bool succeeded = (display).start();
    if (succeeded)
    {
        InputsListener inputsListener(gameData, display, grid);
        inputsListener.handleInputs([&](int delay) {
            loop(delay);
        });
        (display).close();
    }
}

void GameManager::loop(long delay)
{
    if (gameData.activePiece.empty())
        gameData.activePiece = createNewPiece();

    if (gameData.delaySinceGravity > 1000) // in milliseconds
    {
        bool shifted = shift(gameData.activePiece, display, grid, 0, 1);
        if (!shifted)
        { // if we touched the ground
            for (Puyo puyo : gameData.activePiece)
                grid.content[puyo.x][puyo.y] = puyo.type;
            gameData.activePiece = {};
        }
        gameData.delaySinceGravity = 0;
    }
    else
        gameData.delaySinceGravity += delay;
}

std::vector<Puyo> GameManager::createNewPiece()
{
    std::size_t base = random_index(0, grid.width() - 1);
    std::vector<Puyo> activePiece(2);
    activePiece[0] = Puyo(Grid::PuyoType(random_index(1, 5)), base, 0);
    activePiece[1] = Puyo(Grid::PuyoType(random_index(1, 5)), base + 1, 0);
    return activePiece;
}

std::size_t GameManager::random_index(std::size_t lower, std::size_t higher)
{
    std::uniform_int_distribution<std::size_t> dist(lower, higher);
    return dist(gen);
}