#include "controllers/gridTools.hpp"

/**
 * to detect groups of connected Puyos from a list of points
 * 
 * @param Grid &grid the grid so search in
 * @param std::unordered_set<Coordinates> &starts a set of starting points
 * @param const unsigned int triggerSize the size under which a group is not added
 * 
 * @return std::vector<std::vector<Puyo>> the vector of groups of connected Puyos
 * 
 * @author Thomas Marchand
 * @confidence 5
 **/
std::vector<std::vector<Puyo>> runDetection(Grid &grid,
                                            std::unordered_set<Coordinates> &starts,
                                            const unsigned int triggerSize)
{
    std::vector<std::vector<Puyo>> groups;
    std::vector<std::vector<Grid::PuyoType>> contentSample(grid.width(),
                                                           std::vector<Grid::PuyoType>(grid.height(), Grid::none));
    for (Coordinates coordinates : starts)
    {
        Grid::PuyoType type = grid.content[coordinates.x][coordinates.y];
        Grid clonedGrid = grid;
        std::vector<Puyo> group;
        extractGroup(group, clonedGrid, coordinates);
        bool duplicate = false;
        for (Puyo puyo : group)
        {
            if (contentSample[puyo.x][puyo.y])
            {
                duplicate = true;
                break;
            }
            else
            {
                contentSample[puyo.x][puyo.y] = puyo.type;
            }
        }
        if (!duplicate && group.size() >= triggerSize)
            groups.push_back(group);
    }
    return groups;
}

/**
 * A recursive function to detect groups of connected Puyos from a list 
 * of points, it is a utility function for runDetection that will 
 * 
 * @param std::vector<Puyo> &group a group reference
 * @param Grid &grid the grid to check
 * @param const Coordinates coordinates to analyze connections
 *
 * @author Thomas Marchand
 * @confidence 5 (tested through runDetection tests)
 **/
void extractGroup(std::vector<Puyo> &group,
                  Grid &grid,
                  const Coordinates coordinates)
{
    Puyo puyo = Puyo(grid.content[coordinates.x][coordinates.y],
                     coordinates.x,
                     coordinates.y);
    grid.content[puyo.x][puyo.y] = Grid::none;
    group.push_back(puyo);

    if (puyo.x > 0 && grid.content[puyo.x - 1][puyo.y] == puyo.type)
        extractGroup(group, grid, Coordinates(puyo.x - 1, puyo.y));

    if (puyo.y > 0 && grid.content[puyo.x][puyo.y - 1] == puyo.type)
        extractGroup(group, grid, Coordinates(puyo.x, puyo.y - 1));

    if (puyo.x + 1 < grid.width() && grid.content[puyo.x + 1][puyo.y] == puyo.type)
        extractGroup(group, grid, Coordinates(puyo.x + 1, puyo.y));

    if (puyo.y + 1 < grid.height() && grid.content[puyo.x][puyo.y + 1] == puyo.type)
        extractGroup(group, grid, Coordinates(puyo.x, puyo.y + 1));
}

/**
 * to shift falling piece down one cell (tetrix gravity)
 * 
 * @param Grid &grid the grid to run gravity on
 *
 * @author Thomas Marchand
 * @confidence 5 (tested through runDetection tests)
 **/
void runGravity(Grid &grid)
{
    // find starting points
    std::unordered_set<Coordinates> starts;
    for (std::size_t x = 0; x < grid.width(); x++)
        for (std::size_t y = grid.height() - 1; y >= 1; y--)
            if (grid.content[x][y - 1] && !grid.content[x][y])
            {
                grid.content[x][y] = grid.content[x][y - 1];
                grid.content[x][y - 1] = Grid::none;
                starts.emplace(x, y);
            }

    // run detections
    for (std::vector<Puyo> puyoList : runDetection(grid, starts))
        for (Puyo puyo : puyoList)
            grid.content[puyo.x][puyo.y] = Grid::none;
}

/**
 * to define Coordinates hash (required in order to use unordered_set)
 * 
 * @param const Coordinates &coordinates a Coordinate instance
 *
 * @author Thomas Marchand
 * @confidence 5
 **/
std::size_t std::hash<Coordinates>::operator()(const Coordinates &coordinates) const noexcept
{
    std::hash<std::size_t> size_t_hash;
    return size_t_hash(coordinates.x) ^ size_t_hash(coordinates.y);
}

/**
 * to construct a Coordinates object
 * 
 * @param std::size_t x, position on the x axis
 * @param std::size_t y, position on the y axis
 *
 * @author Thomas Marchand
 * @confidence 5
 **/
Coordinates::Coordinates(std::size_t x, std::size_t y) : x(x), y(y)
{
}

/**
 * to compare two Coordinates objects (required for unordered_set)
 * 
 * @param const Coordinates &other, another instance of Coordinates
 *
 * @author Thomas Marchand
 * @confidence 5
 **/
bool Coordinates::operator==(const Coordinates &other) const
{
    return x == other.x && y == other.y;
}