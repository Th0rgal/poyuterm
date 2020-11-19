cmake_minimum_required(VERSION 3.0)

project(poyuterm VERSION 0.0.1)

# Prepare doctest for other targets to use
find_package(doctest REQUIRED)
include(doctest)
include(common.cmake)

set(SRCS
    src/main.cpp
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

set(LIBS
    ncurses
    pthread
)

add_executable(poyuterm ${SRCS} ${HEADERS})
target_include_directories(poyuterm PUBLIC src/)
target_link_libraries(poyuterm ${LIBS})

# easy way to fix test coverage - disable colors and crash handling
target_compile_definitions(poyuterm PRIVATE
    DOCTEST_CONFIG_COLORS_NONE
    DOCTEST_CONFIG_NO_POSIX_SIGNALS
    DOCTEST_CONFIG_NO_WINDOWS_SEH)

# omit the version and the num test cases skipped from the summary - this way the output will change less often
set(common_args COMMAND $<TARGET_FILE:poyuterm> --no-skipped-summary --no-version)

# Make test executable

# test_grid
add_executable(test_grid tests/grid.cpp ${SRCS} ${HEADERS})
target_compile_features(test_grid PRIVATE cxx_std_17)
target_include_directories(test_grid PUBLIC src/)
target_link_libraries(test_grid PRIVATE doctest::doctest ${LIBS})
doctest_add_test(NAME test_grid ${common_args} -sf=*${f})

# test_inputs
add_executable(test_inputs tests/inputs.cpp ${SRCS} ${HEADERS})
target_compile_features(test_inputs PRIVATE cxx_std_17)
target_include_directories(test_inputs PUBLIC src/)
target_link_libraries(test_inputs PRIVATE doctest::doctest ${LIBS})
doctest_add_test(NAME test_inputs ${common_args} -sf=*${f})