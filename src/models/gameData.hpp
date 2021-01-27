#pragma once
#include <vector>
#include "models/grid.hpp"
#include "models/puyo.hpp"
#include "controllers/activePiece.hpp"

struct GameData
{
    enum GameState
    {
        running = 0,
        ended = 1,
        menu = 2
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

    unsigned int score = 0;
    bool loaded = false;
    GameData();
    unsigned int addScore(std::size_t groupSize, unsigned int combosIndex, unsigned int groupsNumber);
    ActivePiece activePiece;
    long delaySinceTick;
};