cmake_minimum_required(VERSION 3.0)

project(poyuterm)

# tests
enable_testing()
add_executable(test_fail tests/fail.cpp)

set(SRCS
    src/main.cpp
    src/game/game.cpp
    )
    
set(HEADERS
    src/game/game.h
    )

add_executable(poyuterm ${SRCS} ${HEADERS})
target_link_libraries(poyuterm ncurses)

add_test(NAME fail COMMAND test_fail)