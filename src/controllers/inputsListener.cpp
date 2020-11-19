#include <ncurses.h>
#include <functional>
#include "controllers/inputsListener.hpp"
#include <chrono>

using namespace std::chrono;

InputsListener::InputsListener(GameData &gameData, Grid &grid) : gameData(gameData), grid(grid)
{
}

void InputsListener::handleInputs(const std::function<void(int)> &loop)
{
    int inputCode;
    high_resolution_clock::time_point previousTime = high_resolution_clock::now();
    while ((inputCode = getch()) != KEY_ENTER)
    {
        if (inputCode == ERR)
        {
            loop(int((high_resolution_clock::now() - previousTime).count() * 1e-6));
            previousTime = high_resolution_clock::now();
        }
        else
        {
            onKeyPressed(inputCode);
        }
    }
}

void InputsListener::onKeyPressed(int code)
{
    switch (code)
    {
    case KEY_LEFT:
        translateLeft();
        break;

    case KEY_RIGHT:
        translateRight();
        break;

    case KEY_DOWN:
        translateDown();
        break;
    }
}

void InputsListener::translateLeft()
{
    shift(-1, 0);
}

void InputsListener::translateRight()
{
    shift(1, 0);
}

void InputsListener::translateDown()
{
    shift(0, -1);
}

void InputsListener::shift(int x, int y)
{
    std::vector<std::pair<int, int>> updatedPiece(2);
    vector<vector<Grid::PuyoType>> clonedContent = grid.content;
    for (int i = 0; i < gameData.activePiece.size(); i++)
    {
        updatedPiece[i] = gameData.activePiece[i];
        updatedPiece[i].first += x;
        // avoid impossible x
        if (updatedPiece[i].first < 0 || updatedPiece[i].first >= grid.width())
            return;

        // avoid impossible y
        updatedPiece[i].second += y;
        if (updatedPiece[i].second < 0 || updatedPiece[i].second >= grid.width())
            return;

        // avoid overwriting
        if (grid.content[updatedPiece[i].first][updatedPiece[i].second])
            return;

        Grid::PuyoType type = grid.content[gameData.activePiece[i].first][gameData.activePiece[i].second];
        clonedContent[gameData.activePiece[i].first][gameData.activePiece[i].second] = Grid::none;
        clonedContent[updatedPiece[i].first][updatedPiece[i].second] = type;
    }
    gameData.activePiece = updatedPiece;
    grid.content = clonedContent;
}