#include "controllers/gameManager.hpp"
#include "controllers/io/parser.hpp"
#include "models/gameData.hpp"
#include "models/grid.hpp"

int main(int argsSize, char *args[])
{

    Parser parser = (argsSize >= 2) ? Parser(args[1]) : Parser();

    // load controllers
    GameManager(parser).start();

    return 0;
}