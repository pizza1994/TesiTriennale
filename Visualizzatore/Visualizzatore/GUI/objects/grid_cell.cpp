#include "grid_cell.h"





GridCell::GridCell()
{

}

GridCell::GridCell(std::vector<Pointd> vertices)
{
    xyz = vertices;
}


void GridCell::setAdjCells(std::vector<&GridCell> adjCells)
{

    this->adjCells = adjCells;

}



std::vector<&GridCell> GridCell::getAdjCells()
{
    return adjCells;
}


std::vector<Pointd> GridCell::getVertices()
{
    return xyz;
}


