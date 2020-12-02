#include <doctest/doctest.h>
#include "models/puyo.hpp"

TEST_CASE("testing default constructor")
{
    Puyo puyo;
    CHECK(puyo.type == Grid::none);
    CHECK(puyo.x == 0);
    CHECK(puyo.y == 0);
}

TEST_CASE("testing constructor")
{
    Puyo puyo(Grid::red, 4, 5);
    CHECK(puyo.type == Grid::red);
    CHECK(puyo.x == 4);
    CHECK(puyo.y == 5);
}

TEST_CASE("testing move function")
{
    Puyo puyo(Grid::red, 4, 5);

    puyo.move(1, -1);
    CHECK(puyo.type == Grid::red);
    CHECK(puyo.x == 5);
    CHECK(puyo.y == 4);

    puyo.move(0, -1);
    CHECK(puyo.type == Grid::red);
    CHECK(puyo.x == 5);
    CHECK(puyo.y == 3);
}

TEST_CASE("testing comparison function")
{
    Puyo puyo(Grid::red, 4, 5);

    puyo.move(1, -1);
    CHECK(puyo == Puyo(Grid::red, 5, 4));

    puyo.move(0, -1);
    CHECK(puyo == Puyo(Grid::red, 5, 3));
}
