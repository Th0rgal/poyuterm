#include "models/gameData.hpp"
#include "views/display.hpp"
#include "views/gamescreen.hpp"
#include <math.h>

/**
 * to intialize the GameData
 * 
 * @author Thomas Marchand
 **/
GameData::GameData()
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