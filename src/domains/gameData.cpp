#include "domains/gameData.hpp"
#include "views/display.hpp"

/**
 * to intialize the GameData
 **/
GameData::GameData() : activePiece({}), delaySinceGravity(0)
{
}

/**
 * to shift the falling piece in gameData and on the grid
 * @param std::vector<Puyo> &activePiece the falling piece to shift
 * @param Grid::Grid constraint the grid to compare to
 * @param int x, -1 <= x <= 1, the shift on the x axis
 * @param int y, -1 <= y <= 1, the shift on the y axis
 * @return bool true if the piece has been shifted
 **/
bool shift(std::vector<Puyo> &activePiece, Grid constraint, int x, int y)
{
    const size_t size = activePiece.size();
    std::vector<Puyo> updatedPiece(size);

    for (size_t i = 0; i < size; i++)
    {
        Puyo puyo = activePiece[i];

        // avoid impossible x
        if (static_cast<int>(puyo.x) + x < 0 ||
            static_cast<int>(puyo.x) + x >= static_cast<int>(constraint.width()))
            return false;

        // avoid impossible y
        if (static_cast<int>(puyo.y) + y < 0 ||
            static_cast<int>(puyo.y) + y >= static_cast<int>(constraint.height()))
            return false;

        puyo.move(x, y);

        // avoid overwriting
        if (constraint.content[puyo.x][puyo.y])
            return false;

        updatedPiece[i] = puyo;
    }

    for (std::size_t i = 0; i < updatedPiece.size(); i++)
        activePiece[i] = updatedPiece[i];

    return true;
}

/**
 * to shift the falling piece in gameData and on the grid and update the display
 * @param std::vector<Puyo> &activePiece the falling piece to shift
 * @param ConsoleDisplay &display the display to update
 * @param Grid::Grid constraint the grid to compare to
 * @param int x, -1 <= x <= 1, the shift on the x axis
 * @param int y, -1 <= y <= 1, the shift on the y axis
 * @return bool true if the piece has been shifted
 **/
bool shift(std::vector<Puyo> &activePiece, ConsoleDisplay &display, Grid constraint, int x, int y)
{
    const std::vector<Puyo> clone = activePiece;
    if (!shift(activePiece, constraint, x, y))
        return false;

    for (std::size_t i = 0; i < clone.size(); i++)
        display.setCell(clone[i].x, clone[i].x, Grid::none);

    for (std::size_t i = 0; i < activePiece.size(); i++)
    {
        display.setCell(activePiece[i].x, activePiece[i].y, activePiece[i].type);
    }

    return true;
}

/**
 * Empty constructor for puyo. Will create an instance
 * of type none with (0,0) coordinates
 **/
Puyo::Puyo() : type(Grid::none), x(0), y(0)
{
}

/**
 * Constructor of a Puyo
 * @param Grid::PuyoType type the type of the Puyo
 * @param std::size_t x, position of the Puyo on the x axis
 * @param std::size_t y, position of the Puyo on the y axis
 **/
Puyo::Puyo(Grid::PuyoType type,
           std::size_t x,
           std::size_t y) : type(type),
                            x(x), y(y)
{
}

/**
 * Shift your puyo on x and y axis
 * @param int xAdd, shift to add to the x axis
 * @param int yAdd, shift to add to the y axis
 **/
void Puyo::move(int xAdd,
                int yAdd)
{
    x += xAdd;
    y += yAdd;
}

bool Puyo::operator==(const Puyo &other) const
{
    return type == other.type && x == other.x && y == other.y;
}