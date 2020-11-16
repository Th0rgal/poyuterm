cmake_minimum_required(VERSION 3.0)

project(poyuterm)

set(SRCS
    src/main.cpp
    src/controllers/gameManager.cpp
    src/domains/grid.cpp
    )
    
set(HEADERS
    src/controllers/gameManager.hpp
    src/domains/grid.hpp
    )

add_executable(poyuterm ${SRCS} ${HEADERS})
target_include_directories(poyuterm PUBLIC src/)
target_link_libraries(poyuterm ncurses)

# tests
enable_testing()
add_executable(test_grid_gravity tests/grid_gravity.cpp)
target_include_directories(test_grid_gravity PUBLIC src/)
add_test(NAME grid_gravity COMMAND test_grid_gravity)
