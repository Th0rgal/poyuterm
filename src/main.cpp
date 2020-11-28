#include "controllers/gameManager.hpp"
#include "models/gameData.hpp"
#include "models/grid.hpp"

int main(int argsSize, char *args[])
{

    std::vector<std::vector<Grid::PuyoType>> content(6, std::vector<Grid::PuyoType>(12));
    if (argsSize >= 1)
    {
        char *fileName = args[0];
    }

    // load controllers
    GameManager(GameData(), Grid(content)).start();

    return 0;
}