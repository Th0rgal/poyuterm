#include "domains/grid.hpp"
#include <iostream>

/**
 * to intialize the grid with a 2d vector
 * @param vector<vector<PuyoType>> the initial grid content
 **/
Grid::Grid(vector<vector<PuyoType>> initialGrid) : content(initialGrid)
{
}

/**
 * to make the falling puyo fall from a box
 * @return bool false if all puyo have fallen down
 **/
bool Grid::triggerGravity()
{
    vector<vector<PuyoType>> clone = content;
    for (int x = 0; x < clone.size(); x++)
        for (int y = 0; y < clone[0].size() - 1; y++)
            if (clone[x][y] && !clone[x][y + 1])
            {
                content[x][y + 1] = clone[x][y];
                content[x][y] = none;
            }

    for (int x = 0; x < content.size(); x++)
        for (int y = 0; y < content[0].size() - 1; y++)
            if (content[x][y] && !content[x][y + 1])
                return false;
    return true;
}

/**
 * to delete all combinations of linked puyos with 
 * a minimum size of 4
 **/
void Grid::removeAdjectives()
{
    int combinationsColone = 0;
    int combinationsLigne = 0;
    bool destruction = true;
    int xCombianison = 0, yCombinaison = 0;
    PuyoType type = none;
    for(int x = content.size() - 1; x >= 0; x++){
        for(int y = 0; y < content.size(); y++){
            type = content[x][y];
            combinationsColone = 1;
            combinationsLigne = 1;
            xCombianison = x;
            yCombinaison = y;
            while(content[x][yCombinaison] == type){
                yCombinaison++;
                combinationsLigne++;
            }
            while(content[yCombinaison][x] == type){
                xCombianison++;
                combinationsColone--;
            }
            if(yCombinaison > xCombianison){
                for(int i = y; i < yCombinaison; i++){
                    content[x][i] = none;
                }
            }else {
                for(int i = x; i < xCombinaison; i++){
                    content[i][y] = none;
                }
            }
        }
    }
    return;
}