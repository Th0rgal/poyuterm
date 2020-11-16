#include "game.hpp"
#include "../grid/grid.hpp"
#include "../grid/grid.cpp"

using namespace game;

void game::loop() {
    grid::trigger_gravity();
}