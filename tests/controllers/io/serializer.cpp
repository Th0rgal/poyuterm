#include <doctest/doctest.h>
#include "controllers/io/serializer.hpp"

TEST_CASE("testing serializer")
{
    Serializer serializer{"./tests/inputs/example_output.txt"};
    serializer.close();
    // we want to check if it is errorless
}