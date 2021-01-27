cmake_minimum_required(VERSION 3.0)

project(poyuterm VERSION 0.0.1)

set(SRCS
    src/models/gameData.cpp
    src/models/grid.cpp
    src/models/puyo.cpp

    src/controllers/activePiece.cpp
    src/controllers/gridTools.cpp
    src/controllers/io/parser.cpp
    src/controllers/io/serializer.cpp
    src/controllers/solver/solverManager.cpp
)

set(HEADERS
    src/models/gameData.hpp
    src/models/grid.hpp
    src/models/puyo.hpp

    src/controllers/activePiece.hpp
    src/controllers/gridTools.hpp
    src/controllers/io/parser.hpp
    src/controllers/io/serializer.hpp
    src/controllers/solver/solverManager.hpp
)

add_executable(poyuterm src/main.cpp ${SRCS} ${HEADERS})
target_compile_features(poyuterm PRIVATE cxx_std_17)
target_include_directories(poyuterm PUBLIC src/)