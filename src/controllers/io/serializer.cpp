#include "controllers/io/serializer.hpp"
#include <fstream>

Serializer::Serializer(const char *fileName)
{
    file.open(fileName);
}

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

void Serializer::writeGrid(Grid &grid)
{
    for (std::size_t y = 0; y < grid.height(); y++)
    {
        for (std::size_t x = 0; x < grid.width(); x++)
            file << toLetter(grid.content[x][y]);
        file << std::endl;
    }
}

void Serializer::writeScore(unsigned int score)
{
    file << score << " points";
}

void Serializer::writePiece(ActivePiece &piece)
{
    file << toLetter(piece.side.type) << toLetter(piece.center.type) << std::endl;
    unsigned int column = ((piece._orientation == ActivePiece::west) ? piece.side.x : piece.center.x) + 1;
    file << piece._orientation << " " << column << std::endl;
}

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