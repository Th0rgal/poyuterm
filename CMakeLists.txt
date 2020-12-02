cmake_minimum_required(VERSION 3.0)

project(poyuterm VERSION 0.0.1)

# Prepare doctest for other targets to use
find_package(doctest REQUIRED)
include(doctest)

set(SRCS
    src/controllers/gameManager.cpp
    src/controllers/gridTools.cpp
    src/controllers/puyo.cpp
    src/controllers/activePiece.cpp
    src/controllers/tetrix.cpp
    src/controllers/listeners/inputsListener.cpp
    src/controllers/listeners/gridListener.cpp
    src/controllers/listeners/menuListener.cpp
    src/controllers/io/parser.cpp
    src/controllers/io/serializer.cpp
    src/controllers/solver/solverManager.cpp

    src/models/gameData.cpp
    src/models/grid.cpp
    src/models/puyo.cpp

    src/views/display.cpp
    src/views/gamescreen.cpp
    src/views/menu/menuscreen.cpp
    src/views/menu/menustart.cpp
    src/views/menu/menugameover.cpp
    src/views/music/music.cpp
)

set(HEADERS
    src/controllers/gameManager.hpp
    src/controllers/gridTools.hpp
    src/controllers/activePiece.hpp
    src/controllers/listeners/inputsListener.hpp
    src/controllers/io/parser.hpp
    src/controllers/io/serializer.hpp
    src/controllers/solver/solverManager.hpp

    src/models/gameData.hpp
    src/models/grid.hpp
    src/models/puyo.hpp

    src/views/display.hpp
    src/views/gamescreen.hpp
    src/views/menu/menuscreen.hpp
    src/views/music/music.hpp
)

set(TESTS
    tests/tests.cpp
    tests/puyo.cpp
    tests/grid.cpp
    tests/gridTools.cpp
    tests/activePiece.cpp
)

set(LIBS
    ncurses
    pthread
    menu
    sfml-audio
)

add_executable(poyuterm src/main.cpp ${SRCS} ${HEADERS})
target_compile_features(poyuterm PRIVATE cxx_std_17)
target_include_directories(poyuterm PUBLIC src/)
target_link_libraries(poyuterm ${LIBS})

# Make test executable

# tests
add_executable(run_tests ${TESTS} ${SRCS} ${HEADERS})
target_compile_features(run_tests PRIVATE cxx_std_17)
target_include_directories(run_tests PUBLIC src/)
target_link_libraries(run_tests PRIVATE doctest::doctest ${LIBS})