#include "controllers/io/parser.hpp"

/**
 * Default constructor
 * 
 * @author Thomas Marchand
 * @confidence 5
 **/
Parser::Parser()
{
    enabled = false;
}

/**
 * Constructor
 * 
 * @param const char *fileName a fileName
 * 
 * @author Thomas Marchand
 * @confidence 5
 **/
Parser::Parser(const char *fileName) : fileName(fileName)
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

/**
 * Translate a letter to a PuyoType
 * 
 * @param char letter the letter to translate
 * 
 * @return PuyoType the translated letter
 * 
 * @author Thomas Marchand
 * @confidence 5
 **/
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

/**
 * Read the next ActivePiece for simulation
 * 
 * @param Grid &constraint to use for validation
 * 
 * @return bool true if activePiece has been successfully changed
 * @author Thomas Marchand
 * @confidence 5
 **/
bool Parser::next(Grid &constraint)
{
    if (gameMode == GameData::simulation)
    {
        std::string activePieceData;
        unsigned int rotations;
        unsigned int column;
        if (file >> activePieceData && file >> rotations && file >> column)
        {
            Puyo side = Puyo(toPuyoType(activePieceData[0]), column - 1, 1);
            Puyo center = Puyo(toPuyoType(activePieceData[1]), column - 1, 0);
            activePiece = ActivePiece(center, side, 1);
            activePiece.rotate(constraint, (rotations - 1) % 4);
            return true;
        }
    }
    return false;
}

/**
 * Read the next ActivePiece for solo
 * 
 * @param std::size_t column the place to spawn the piece
 * 
 * @return bool true if activePiece has been successfully oaded
 * @author Thomas Marchand
 * @confidence 5
 **/
bool Parser::next(std::size_t column)
{
    if (gameMode == GameData::solo || gameMode == GameData::ia)
    {
        std::string activePieceData;
        if (file >> activePieceData)
        {
            Puyo side = Puyo(toPuyoType(activePieceData[0]), column, 0);
            Puyo center = Puyo(toPuyoType(activePieceData[1]), column + 1, 0);
            activePiece = ActivePiece(center, side, 0);
            return true;
        }
    }
    return false;
}

void Parser::close()
{
    file.close();
}