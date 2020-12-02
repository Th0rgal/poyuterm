#include "controllers/activePiece.hpp"
#include "controllers/io/parser.hpp"
#include <vector>

struct Snapshot
{
    Snapshot(unsigned int score, Grid grid, std::size_t index);
    unsigned int _score;
    Grid _grid;
    std::size_t _index;
    void update(Snapshot snapshot);
};

class Solver
{
public:
    Solver(Parser &parser);
    void write();
    void start();
    std::vector<ActivePiece> _pieces;
    unsigned int teleportDownVirtually(Grid &grid, ActivePiece &activePiece);

private:
    void browse(Snapshot &output, Snapshot input, unsigned int calls);
    void teleportDownVirtually(Grid &grid, GameData &gameData);
};

unsigned int getScore(std::size_t groupSize, unsigned int combosIndex, unsigned int groupsNumber);