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

void Puyo::move(std::size_t xAdd,
                std::size_t yAdd)
{
    x += xAdd;
    y += yAdd;
}

bool Puyo::operator==(const Puyo &other) const
{
    return type == other.type && x == other.x && y == other.y;
}

/**
 * to shift the falling piece in gameData and on the grid
 * @param std::vector<Puyo> &activePiece the falling piece to shift
 * @param Grid::Grid constraint the grid to compare to
 * @param int x, -1 <= x <= 1, the shift on the x axis
 * @param int y, -1 <= y <= 1, the shift on the y axis
 * 
 **/
bool shift(std::vector<Puyo> &activePiece, Grid constraint, int x, int y)
{
    const size_t size = activePiece.size();
    std::vector<Puyo> updatedPiece(size);

    for (size_t i = 0; i < size; i++)
    {
        Puyo puyo = activePiece[i];

        // avoid impossible x
        if (puyo.x < static_cast<unsigned int>(x) ||
            static_cast<int>(puyo.x) + x >= static_cast<int>(constraint.width()))
            return false;

        // avoid impossible y
        if (puyo.y < static_cast<unsigned int>(y) ||
            static_cast<int>(puyo.y) + y >= static_cast<int>(constraint.height()))
            return false;

        puyo.move(static_cast<unsigned int>(x), static_cast<unsigned int>(y));

        // avoid overwriting
        if (constraint.content[puyo.x][puyo.y])
            return false;

        updatedPiece[i] = puyo;
    }

    // shift
    for (std::size_t i = 0; i < updatedPiece.size(); i++)
        activePiece[i] = updatedPiece[i];

    return true;
}