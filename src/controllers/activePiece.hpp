#include <functional>
#include "models/puyo.hpp"

class ActivePiece
{

public:
    ActivePiece(Puyo center, Puyo side, unsigned int orientation);
    Puyo center;
    Puyo side;
    bool rotate(Grid &grid);
    void map(const std::function<void(Puyo)> &function);

private:
    enum Orientation
    {
        west = 0,
        south = 1,
        east = 2,
        north = 3
    };
    Orientation orientation;
};
