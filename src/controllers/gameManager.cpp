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
GameManager::GameManager(Parser &parser) : parser(parser),
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
    _display.showMenuStart();
    if (_display.started)
    {
        InputsListener inputsListener(_gameData, _display, _grid);
        inputsListener.handleInputs([&](int delay) {
            loop(delay);
        });
        _display.close();
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
    if (_gameData.state == GameData::running)
        switch (_gameData.mode)
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
ActivePiece GameManager::createNewPiece()
{
    std::size_t base = random_index(0, _grid.width() - 2);
    ActivePiece activePiece;
    if (parser.enabled)
    {
        if (!parser.next(base))
        {
            _gameData.state = GameData::ended;
            activePiece.empty = true;
            return activePiece;
        }
        activePiece = parser.activePiece;
    }
    else
    {
        Puyo side = Puyo(Grid::PuyoType(random_index(1, 5)), base, 0);
        Puyo center = Puyo(Grid::PuyoType(random_index(1, 5)), base + 1, 0);
        activePiece = ActivePiece(center, side, 0);
    }

    activePiece.map([&](Puyo puyo) {
        if (_grid.content[puyo.x][puyo.y])
        {
            _gameData.state = GameData::ended;
            activePiece.empty = true;
            return;
        }
        (*_display.game).setCell(puyo.x, puyo.y, puyo.type);
    });
    bool empty = activePiece.empty;
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