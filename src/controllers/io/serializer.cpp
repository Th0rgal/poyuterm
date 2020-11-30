#include "controllers/io/serializer.hpp"
#include <fstream>

Serializer::Serializer(const char *fileName)
{
    file.open(fileName);
}

void Serializer::writeGrid(Grid &grid)
{
    for (std::size_t y = 0; y < grid.height(); y++)
    {
        for (std::size_t x = 0; x < grid.width(); x++)
        {
            char letter;
            switch (grid.content[x][y])
            {
            case Grid::none:
                letter = '.';
                break;
            case Grid::red:
                letter = 'R';
                break;
            case Grid::green:
                letter = 'V';
                break;
            case Grid::yellow:
                letter = 'J';
                break;
            case Grid::blue:
                letter = 'B';
                break;
            case Grid::pink:
                letter = 'M';
                break;
            default:
                letter = '?';
            }
            file << letter;
        }
        file << std::endl;
    }
}

void Serializer::writeScore(unsigned int score)
{
    file << score << " points";
}