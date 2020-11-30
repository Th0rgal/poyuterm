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
    std::vector<Puyo> activePiece;
    long delaySinceTick;
};