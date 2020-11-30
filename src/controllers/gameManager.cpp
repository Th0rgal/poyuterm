#include "controllers/gameManager.hpp"
#include "models/gameData.hpp"
#include "controllers/listeners/inputsListener.hpp"
#include <stdlib.h>
#include <ncurses.h>
#include <string>
#include <iostream>
#include "views/display.hpp"

/**
 * to intialize a GameManager object
 * @param GameData &gameData GameData instance passed by reference
 * @param Grid &grid a Grid instance passed by reference
 * @param Display &display a GameDisplay instance passed by reference
 * 
 * @author Thomas Marchand
 **/
GameManager::GameManager(GameData gameData,
                         Grid grid,
                         Parser &parser) : gameData(gameData),
                                          grid(grid),
                                          parser(parser),
                                          rd(),
                                          gen(rd())
{
}

/**
 * to load the display and start listening to inputs. The inputsListener
 * takes a callback to the loop function.
 * 
 * @author Thomas Marchand
 **/
void GameManager::start()
{
    display.showMenu();
    if (display.started)
    {
        InputsListener inputsListener(gameData, display, grid);
        inputsListener.handleInputs([&](int delay) {
            loop(delay);
        });
        display.close();
    }
}

/**
 * The game loop called everytime a user input hasn't been detected
 * @param long delay the delay in nanoseconds with the previous loop call
 * 
 * @author Thomas Marchand
 **/
void GameManager::loop(long delay)
{
    if (gameData.state == GameData::running)
        switch (gameData.mode)
        {
        case GameData::tetrix:
            tetrixLoop(delay);
            break;

        case GameData::solo:
            puyoLoop(delay);
            break;

        case GameData::simulation:
            simulationLoop(delay);
            break;

        default:
            break;
        }
}

/**
 * to create a new movingPiece (a Puyo's vector)
 * @return std::vector<Puyo> a vector of two linked Puyo generated randomly
 * on the first line (y:=0) with a random color
 * 
 * @author Thomas Marchand
 **/
std::vector<Puyo> GameManager::createNewPiece()
{
    std::size_t base = random_index(0, grid.width() - 2);
    std::vector<Puyo> activePiece(2);
    activePiece[0] = Puyo(Grid::PuyoType(random_index(1, 5)), base, 0);
    activePiece[1] = Puyo(Grid::PuyoType(random_index(1, 5)), base + 1, 0);
    for (Puyo puyo : activePiece)
    {
        if (grid.content[puyo.x][puyo.y])
        {
            gameData.state = GameData::ended;
            return {};
        }
        (*display.game).setCell(puyo.x, puyo.y, puyo.type);
    }
    return activePiece;
}

/**
 * to generate a random number between two positive integers
 * @param std::size_t lower the lowest possible number
 * @param std::size_t lower the biggest possible number
 * @return std::size_t a positive number between lower and higher
 * 
 * @author Thomas Marchand
 **/
std::size_t GameManager::random_index(std::size_t lower, std::size_t higher)
{
    std::uniform_int_distribution<std::size_t> dist(lower, higher);
    return dist(gen);
}