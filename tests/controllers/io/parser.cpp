#include <doctest/doctest.h>
#include "controllers/io/parser.hpp"

TEST_CASE("a")
{
    Parser parser{"./tests/inputs/example_simulation.txt"};
}