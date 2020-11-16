#include "controllers/gameManager.hpp"
#include "domains/grid.hpp"

using namespace gameManager;
using namespace grid;

void gameManager::loop() {
    trigger_gravity();
}