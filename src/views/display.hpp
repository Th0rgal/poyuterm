#pragma once

#include <ncurses.h>
#include "views/gamescreen.hpp"
#include "views/menuscreen.hpp"

class Display
{
public:
    Display();

    bool started = false;
    bool start();
    void close();
    void showError();

    void showMenu();
    void showGame();

    GameScreen game;
    MenuScreen menu;

private:
};