#include "models/gameData.hpp"
#include "views/display.hpp"
#include "views/gamescreen.hpp"
#include <math.h>

/**
 * to initialize the GameData
 * 
 * @author Thomas Marchand
 * @confidence 5
 **/
GameData::GameData()
{
    loaded = true;
}

/**
 * to calculate and add the score
 * @param std::size_t groupSize the amount of Puyos in the detected group
 * @param unsigned int combosIndex the index of the combos (starting à 1)
 * @param unsigned int groupsNumber the amount of detected groups
 * 
 * @return unsigned int the sum of the current score and the newly calculated 
 * score bonus with a limit of 999999
 * 
 * @confidence 5
 **/
unsigned int GameData::addScore(std::size_t groupSize, unsigned int combosIndex, unsigned int groupsNumber)
{
    score = score + 10 * groupSize * (pow(4, combosIndex) + pow(3, groupsNumber));
    if (score > 999999)
        score = 999999;
    return score;
}