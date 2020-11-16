cmake_minimum_required(VERSION 3.0)

project(poyuterm VERSION 0.0.1)

# Prepare doctest for other targets to use
find_package(doctest REQUIRED)

set(SRCS
    src/main.cpp
    src/controllers/gameManager.cpp

    src/domains/gameData.cpp
    src/domains/grid.cpp

    src/views/display.cpp
    )

set(HEADERS
    src/controllers/gameManager.hpp

    src/domains/gameData.hpp
    src/domains/grid.hpp

    src/views/display.hpp
    )

add_executable(poyuterm ${SRCS} ${HEADERS})
target_include_directories(poyuterm PUBLIC src/)
target_link_libraries(poyuterm ncurses)


# Make test executable
add_executable(test_grid tests/grid.cpp ${SRCS} ${HEADERS})
target_compile_features(test_grid PRIVATE cxx_std_17)
target_include_directories(test_grid PUBLIC src/)
target_link_libraries(test_grid PRIVATE ncurses doctest::doctest)
