cmake_minimum_required(VERSION 3.0)

project(poyuterm VERSION 0.0.1)

# Prepare doctest for other targets to use
find_package(doctest REQUIRED)
include(doctest)

set(SRCS
    src/controllers/gameManager.cpp
    src/controllers/inputsListener.cpp

    src/domains/gameData.cpp
    src/domains/grid.cpp

    src/views/display.cpp
    )

set(HEADERS
    src/controllers/gameManager.hpp
    src/controllers/inputsListener.hpp

    src/domains/gameData.hpp
    src/domains/grid.hpp

    src/views/display.hpp
    )

set(TESTS
    tests/tests.cpp
    tests/grid.cpp
    tests/inputs.cpp
    )

set(LIBS
    ncurses
    pthread
)

add_executable(poyuterm src/main.cpp ${SRCS} ${HEADERS})
target_include_directories(poyuterm PUBLIC src/)
target_link_libraries(poyuterm ${LIBS})

# Make test executable

# tests
add_executable(run_tests ${TESTS} ${SRCS} ${HEADERS})
target_compile_features(run_tests PRIVATE cxx_std_17)
target_include_directories(run_tests PUBLIC src/)
target_link_libraries(run_tests PRIVATE doctest::doctest ${LIBS})