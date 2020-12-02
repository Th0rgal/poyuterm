#include <doctest/doctest.h>
#include "models/gameData.hpp"
#include <iostream>

TEST_CASE("testing the default constructor")
{
    GameData gameData;

    CHECK(gameData.loaded == true);
    CHECK(gameData.state == GameData::menu);
    CHECK(gameData.mode == GameData::running);
}

TEST_CASE("testing the addScore")
{
    GameData gameData;
    CHECK(gameData.addScore(5, 2, 3) == 2150);
    CHECK(gameData.addScore(4, 1, 1) == 2150 + 280);
    CHECK(gameData.addScore(6, 7, 5) == 999999);
}