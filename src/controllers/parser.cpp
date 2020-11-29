#include "controllers/parser.hpp"
#include "controllers/gridTools.hpp"
#include <string>

Parser::Parser(char *fileName)
{
    std::ifstream file(fileName);
    if (!file)
        throw "Poyuterm was unable to open this file!";
    std::string data;
    file >> data;
    if (data != "MODE")
        throw "Invalid file format";

    file >> data;
    if (data == "SIMULATION")
        gameMode == GameData::simulation;
    else if (data == "SOLO")
        gameMode == GameData::solo;
    else if (data == "IA")
        gameMode == GameData::ia;
    else
        throw "Invalid game mode";
}

bool Parser::next(Grid &constraint)
{
    if (gameMode == GameData::simulation)
    {
        activePiece = std::vector<Puyo>();
        std::string activePieceData;
        unsigned int rotations;
        unsigned int column;
        if (file >> activePieceData && file >> rotations && file >> column)
        {
            for (char letter : activePieceData)
            {
                switch (letter)
                {
                case 'R':
                    activePiece.emplace_back(Grid::red, column - 1, 0);
                    break;
                case 'V':
                    activePiece.emplace_back(Grid::green, column - 1, 0);
                    break;
                case 'J':
                    activePiece.emplace_back(Grid::yellow, column - 1, 0);
                    break;
                case 'B':
                    activePiece.emplace_back(Grid::blue, column - 1, 0);
                    break;
                case 'M':
                    activePiece.emplace_back(Grid::pink, column - 1, 0);
                    break;
                }
                column++;
            }
            for (; rotations != 0; rotations--)
                rotate(activePiece, constraint);
            return true;
        }

        else
        {
            return false;
        }
    }
}