#include "controllers/gameManager.hpp"
#include "domains/gameData.hpp"
#include "controllers/inputsListener.hpp"
#include <stdlib.h>
#include <ncurses.h>
#include <string>
#include <iostream>

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
        const std::vector<Puyo> clone = gameData.activePiece;
        bool shifted = shift(gameData.activePiece, grid, 0, 1);
        if (!shifted)
        { // if we were already on the ground
            for (Puyo puyo : gameData.activePiece)
                grid.content[puyo.x][puyo.y] = puyo.type;
            gameData.activePiece = {};
        }
        else
        {
            gameData.delaySinceGravity = 0;
            for (Puyo puyo : clone)
                display.setCell(puyo.x, puyo.y, Grid::none);
            for (Puyo puyo : gameData.activePiece)
                display.setCell(puyo.x, puyo.y, puyo.type);
        }
    }
    else
        gameData.delaySinceGravity += delay;
}

std::vector<Puyo> GameManager::createNewPiece()
{
    std::size_t base = random_index(0, grid.width() - 2);
    std::vector<Puyo> activePiece(2);
    activePiece[0] = Puyo(Grid::PuyoType(random_index(1, 5)), base, 0);
    activePiece[1] = Puyo(Grid::PuyoType(random_index(1, 5)), base + 1, 0);
    for (Puyo puyo : activePiece)
        display.setCell(puyo.x, puyo.y, puyo.type);
    return activePiece;
}

std::size_t GameManager::random_index(std::size_t lower, std::size_t higher)
{
    std::uniform_int_distribution<std::size_t> dist(lower, higher);
    return dist(gen);
}