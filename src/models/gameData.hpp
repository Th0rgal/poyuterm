#pragma once
#include <vector>
#include "models/grid.hpp"
#include "views/display.hpp"

struct Puyo
{
    Grid::PuyoType type;
    std::size_t x;
    std::size_t y;
    Puyo();
    Puyo(Grid::PuyoType type, std::size_t x, std::size_t y);
    void move(int x, int y);
    bool operator==(const Puyo &other) const;
};

struct GameData
{

    enum GameState
    {
        running = 0,
        won = 1,
        lost = 2,
        menu = 3
    };

    enum GameMode
    {
        solo = 0,
        simulation = 1,
        tetrix = 2,
        ia = 3
    };

    GameMode mode;
    GameState state = menu;

    GameData();
    std::vector<Puyo> activePiece;
    long delaySinceGravity;
};