#include "domains/gameData.hpp"

/**
 * to intialize the GameData
 **/
GameData::GameData() : activePiece({}), delaySinceGravity(0)
{
}

Puyo::Puyo() : type(Grid::none), x(0), y(0)
{
}

Puyo::Puyo(Grid::PuyoType type,
           std::size_t x,
           std::size_t y) : type(type),
                            x(x), y(y)
{
}

void Puyo::add(std::size_t xAdd,
               std::size_t yAdd)
{
    x += xAdd;
    y += yAdd;
}

Puyo Puyo::operator+=(const Puyo &coordinate)
{
    add(coordinate.x, coordinate.y);
    return *this;
}

Puyo Puyo::operator+(Puyo coordinate)
{
    return coordinate += *this;
}
