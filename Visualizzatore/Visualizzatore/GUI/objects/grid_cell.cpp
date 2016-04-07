#include "grid_cell.h"


GridCell::GridCell()
{

}

GridCell::GridCell(std::vector<Pointd> vertices)
{
    xyz = vertices;
}


void GridCell::setAdjCells(std::vector<GridCell*> adjCells)
{

    this->adjCells = adjCells;

}



std::vector<GridCell*> GridCell::getAdjCells() const
{
    return adjCells;
}


std::vector<Pointd> GridCell::getVertices() const
{
    return xyz;
}

Pointd GridCell::getVertex(const int &i) const
{
    return xyz[i];
}


