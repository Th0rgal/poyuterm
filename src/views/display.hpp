#pragma once

#include <ncurses.h>
#include "views/gamescreen.hpp"
#include "views/menuscreen.hpp"
#include <optional>

struct Display
{
    Display();

    bool started = false;
    bool start();
    void close();
    void showError();

    void showMenu();
    void showGame();

    std::optional<GameScreen> game = std::nullopt;
    std::optional<MenuScreen> menu = std::nullopt;
};