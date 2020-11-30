#include "controllers/io/parser.hpp"
#include "controllers/gridTools.hpp"
#include "controllers/activePiece.hpp"
#include <string>

Parser::Parser()
{
    enabled = false;
}

Parser::Parser(char *fileName) : fileName(fileName)
{
    file = std::ifstream(fileName);
    if (!file)
        throw "Poyuterm was unable to open this file!";
    std::string data;
    file >> data;
    if (data != "MODE")
        throw "Invalid file format";

    file >> data;
    if (data == "SIMULATION")
        gameMode = GameData::simulation;
    else if (data == "SOLO")
        gameMode = GameData::solo;
    else if (data == "IA")
        gameMode = GameData::ia;
    else
        throw "Invalid game mode";
    enabled = true;
}

Grid::PuyoType Parser::toPuyoType(char letter)
{
    switch (letter)
    {
    case 'R':
        return Grid::red;
    case 'V':
        return Grid::green;
    case 'J':
        return Grid::yellow;
    case 'B':
        return Grid::blue;
    case 'M':
        return Grid::pink;
    default:
        return Grid::none;
    }
}

bool Parser::next(Grid &constraint)
{
    if (gameMode == GameData::simulation)
    {
        std::string activePieceData;
        unsigned int rotations;
        unsigned int column;
        if (file >> activePieceData && file >> rotations && file >> column)
        {
            Puyo center = Puyo(toPuyoType(activePieceData[0]), column, 0);
            Puyo side = Puyo(toPuyoType(activePieceData[1]), column + 1, 0);
            activePiece = ActivePiece(center, side, 0);

            for (; rotations != 0; rotations--)
                activePiece.rotate(constraint);
            return true;
        }
    }
    return false;
}
