#pragma once

#include <ncurses.h>
#include <vector>
#include <string>

class Screen
{
public:
    void registerWindow(WINDOW *window);
    void close();

private:
    std::vector<WINDOW *> windows;
};