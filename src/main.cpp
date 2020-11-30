#include "controllers/gameManager.hpp"
#include "controllers/io/parser.hpp"
#include "models/gameData.hpp"
#include "models/grid.hpp"

int main(int argsSize, char *args[])
{

    std::vector<std::vector<Grid::PuyoType>> content(6, std::vector<Grid::PuyoType>(12));
    Parser parser = (argsSize >= 2) ? Parser(args[1]) : Parser();

    // load controllers
    GameManager(GameData(), Grid(content), parser).start();

    return 0;
}