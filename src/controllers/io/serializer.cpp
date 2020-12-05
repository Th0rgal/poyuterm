#include "controllers/io/serializer.hpp"

/**
 * Constructor
 * 
 * @param const char *fileName the output file
 * 
 * @author Thomas Marchand
 * @confidence 5
 **/
Serializer::Serializer(const char *fileName)
{
    file.open(fileName);
}

/**
 * to write the GameMode to the output file
 * 
 * @param GameData::GameMode mode the GameMode
 * 
 * @author Thomas Marchand
 * @confidence 3: impossible to test
 **/
void Serializer::writeMode(GameData::GameMode mode)
{
    file << "MODE ";
    switch (mode)
    {
    case GameData::simulation:
        file << "SIMULATION";
        break;
    case GameData::ia:
        file << "IA";
        break;
    case GameData::tetrix:
        file << "TETRIX";
        break;
    case GameData::solo:
        file << "SOLO";
        break;
    default:
        file << "?";
        break;
    }
    file << std::endl;
}

/**
 * to write the grid to the output file
 * 
 * @param Grid &grid the grid reference
 * 
 * @author Thomas Marchand
 * @confidence 3: impossible to test
 **/
void Serializer::writeGrid(Grid &grid)
{
    for (std::size_t y = 0; y < grid.height(); y++)
    {
        for (std::size_t x = 0; x < grid.width(); x++)
            file << toLetter(grid.content[x][y]);
        file << std::endl;
    }
}

/**
 * to write the score to the output file
 * 
 * @param unsigned int score the score to write
 * 
 * @author Thomas Marchand
 * @confidence 3: impossible to test
 **/
void Serializer::writeScore(unsigned int score)
{
    file << score << " points";
}

/**
 * to write an ActivePiece to the output file
 * 
 * @param ActivePiece &piece the piece to write
 * 
 * @author Thomas Marchand
 * @confidence 3: impossible to test
 **/
void Serializer::writePiece(ActivePiece &piece)
{
    file << toLetter(piece.side.type) << toLetter(piece.center.type) << std::endl;
    unsigned int column = ((piece._orientation == ActivePiece::west) ? piece.side.x : piece.center.x) + 1;
    file << piece._orientation << " " << column << std::endl;
}

/**
 * to convert a PuyoType to a human readable char
 * 
 * @param Grid::PuyoType type the PuyoType
 * 
 * @author Thomas Marchand
 * @confidence 3: impossible to test private functions
 **/
char Serializer::toLetter(const Grid::PuyoType type)
{
    switch (type)
    {
    case Grid::none:
        return '.';

    case Grid::red:
        return 'R';

    case Grid::green:
        return 'V';

    case Grid::yellow:
        return 'J';

    case Grid::blue:
        return 'B';

    case Grid::pink:
        return 'M';

    default:
        return '?';
    }
}

/**
 * to close the opened file
 * 
 * @author Thomas Marchand
 * @confidence 3: impossible to test private functions
 **/
void Serializer::close()
{
    file.close();
}