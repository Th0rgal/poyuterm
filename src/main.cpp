#include "controllers/gameManager.hpp"
#include "controllers/io/parser.hpp"
#include "controllers/solver/solverManager.hpp"
#include "models/gameData.hpp"
#include "models/grid.hpp"

/**
 * entry point of the program
 * @param int argsSize size of the splitted start command
 * @param  char *args[] splitted start command
 * 
 * @return exit code (0 if no exceptions occured)
 * @author Thomas Marchand
 * @confidence 3 (not possible to test)
 **/
int main(int argsSize, char *args[])
{

    Parser parser = (argsSize >= 2) ? Parser(args[1]) : Parser();
    if (parser.gameMode == GameData::ia)
    {
        Solver solver{parser};
        solver.start();
    }
    else
        // load controllers
        GameManager(parser).start();

    parser.close();
    return 0;
}