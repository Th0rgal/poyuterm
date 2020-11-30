#include "models/gameData.hpp"
#include "views/display.hpp"
#include "views/gamescreen.hpp"
#include <math.h>

/**
 * to intialize the GameData
 * 
 * @author Thomas Marchand
 **/
GameData::GameData() : activePiece({}), delaySinceTick(0)
{
    loaded = true;
}

unsigned int GameData::addScore(std::size_t groupSize, unsigned int combosIndex, unsigned int groupsNumber)
{
    score = score + 10 * groupSize * (pow(4, combosIndex) + pow(3, groupsNumber));
    if (score > 999999)
        score = 999999;
    return score;
}

/**
 * empty constructor for puyo. Will create an instance
 * of type none with (0,0) coordinates
 * 
 * @author Thomas Marchand
 **/
Puyo::Puyo() : type(Grid::none), x(0), y(0)
{
}

/**
 * constructor of a Puyo
 * @param Grid::PuyoType type the type of the Puyo
 * @param std::size_t x, position of the Puyo on the x axis
 * @param std::size_t y, position of the Puyo on the y axis
 * 
 * @author Thomas Marchand
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
 * 
 * @author Thomas Marchand
 **/
void Puyo::move(int xAdd,
                int yAdd)
{
    x += xAdd;
    y += yAdd;
}

/**
 * comparison operator overloading: to allow comparison between two Puyo
 * @param const Puyo &other the other Puyo instance to compare this with
 * @return bool true if Puyo are similar
 * 
 * @author Thomas Marchand
 **/
bool Puyo::operator==(const Puyo &other) const
{
    return type == other.type && x == other.x && y == other.y;
}

ActivePiece::ActivePiece(Puyo center, Puyo side, unsigned int orientation) : center(center),
                                                                             side(side),
                                                                             orientation(Orientation(orientation))
{
}

bool ActivePiece::rotate(Grid &grid)
{
    switch (orientation)
    {
    case west:
        if (side.x + 1 >= grid.width() || side.y + 1 >= grid.height() || grid.content[side.x + 1][side.y + 1])
            return false;
        side.x += 1;
        side.y += 1;
        break;
    case south:
        if (side.x + 1 >= grid.width() || side.y == 0 || grid.content[side.x + 1][side.y - 1])
            return false;
        side.x += 1;
        side.y -= 1;
        break;
    case east:
        if (center.y + 1 >= grid.height() || side.y == 0 || grid.content[center.x][center.y + 1] || grid.content[side.x][side.y - 1])
            return false;
        center.y += 1;
        side.y -= 1;
        break;
    case north:
        if (center.x + 1 >= grid.width() || center.y == 0 || grid.content[center.x + 1][center.y - 1])
            return false;
        center.x += 1;
        center.y -= 1;
        break;
    }
    orientation = Orientation((orientation + 1) % 4);
}

void ActivePiece::map(const std::function<void(Puyo)> &function)
{
    function(center);
    function(side);
}