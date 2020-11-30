cmake_minimum_required(VERSION 3.0)

project(poyuterm VERSION 0.0.1)

# Prepare doctest for other targets to use
find_package(doctest REQUIRED)
include(doctest)

set(SRCS
    src/controllers/gameManager.cpp
    src/controllers/gridTools.cpp
    src/controllers/puyo.cpp
    src/controllers/tetrix.cpp
    src/controllers/listeners/inputsListener.cpp
    src/controllers/listeners/gridListener.cpp
    src/controllers/listeners/menuListener.cpp
    src/controllers/io/parser.cpp
    src/controllers/io/serializer.cpp

    src/models/gameData.cpp
    src/models/grid.cpp

    src/views/display.cpp
    src/views/gamescreen.cpp
    src/views/menuscreen.cpp
    )

set(HEADERS
    src/controllers/gameManager.hpp
    src/controllers/gridTools.hpp
    src/controllers/listeners/inputsListener.hpp
    src/controllers/io/parser.hpp
    src/controllers/io/serializer.hpp

    src/models/gameData.hpp
    src/models/grid.hpp

    src/views/display.hpp
    src/views/gamescreen.hpp
    src/views/menuscreen.hpp
    )

set(TESTS
    tests/tests.cpp
    tests/grid.cpp
    tests/gridTools.cpp
    )

set(LIBS
    ncurses
    pthread
    menu
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