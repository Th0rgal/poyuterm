cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté hello
project(poyuterm)

# Crée des variables avec les fichiers à compiler
set(SRCS
    src/main.cpp
    src/game/game.cpp
    )
    
set(HEADERS
    src/game/game.h
    )

add_executable(poyuterm ${SRCS} ${HEADERS})