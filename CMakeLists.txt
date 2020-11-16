cmake_minimum_required(VERSION 3.0)

project(poyuterm)

set(SRCS
    src/main.cpp
    src/game/game.cpp
    )
    
set(HEADERS
    src/game/game.hpp
    )

add_executable(poyuterm ${SRCS} ${HEADERS})
target_link_libraries(poyuterm ncurses)

# tests
enable_testing()
add_executable(test_grid_gravity tests/grid_gravity.cpp)
add_test(NAME grid_gravity COMMAND test_grid_gravity)
